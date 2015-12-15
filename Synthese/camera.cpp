#include "camera.h"
#include "ray.h"
#include <QColor>
#include <iostream>
#include <cmath>
#include "mathutils.h"
#include "smoothnoise.h"
#include "sky.h"

#define M_PI 3.14159265358979323846

Camera::Camera(const Vector3D &o, const Vector3D &at, double d):origine(o),dw(d)
{
    Vector3D oat=(at-o);
    w=oat.normalized();
    u=-(w^Vector3D(0,0,1)).normalized();
    v= (w^u).normalized();
    lh=1;
    lw=16/9;
    sphereSamples = Vector3D::randSphere(100);
}

Vector3D mix(const Vector3D& a,const Vector3D& b, double d){
    double quadra=MathUtils::fonctionQuadratique(0,1,d);
    return b*quadra+a*(1-quadra);
}

Vector3D diffuse(const Sky& sky, const Vector3D& normal, const Vector3D diffuseColor)
{
    Vector3D directionLum = -sky.getDirSol().normalized();
    return Vector3D::product(diffuseColor, sky.getLight(directionLum)) * (directionLum * normal);
}

Vector3D specular(const Sky& sky, const Vector3D& normal, const Vector3D& dirCamera, const Vector3D& specularColor, unsigned int coeff)
{
    Vector3D dirCamNormalized = dirCamera.normalized();
    Vector3D directionLum = -sky.getDirSol().normalized();
    Vector3D reflected = ((normal * directionLum) * normal * 2 - directionLum).normalized();
    return Vector3D::product(specularColor, sky.getLight(directionLum)) * MathUtils::power(MathUtils::clamp(0, 1, reflected * dirCamNormalized), coeff);
}

float Camera::ambientOcclusion(const Vector3D& inter, const Vector3D& normale,const Terrain* t, const Vector3D& aBox, const Vector3D& bBox, double pMax) const
{
    Ray raySphere(inter ,inter);
    Vector3D inter2;
    float cpt = 0;
    float visibles = 0;
    bool isBox=false;

    raySphere.origine = inter;
    for(int i = 0; i < sphereSamples.size(); ++i) {
        if(normale*sphereSamples[i] > 0) {
            cpt++;
            raySphere.origine=inter+1*sphereSamples[i];
            raySphere.direction=sphereSamples[i];
            if(!t->intersectAdvancedMax(raySphere,aBox,bBox,pMax,inter2,isBox,20))
                visibles++;

        }
    }
    return visibles/cpt;
}

Vector3D Camera::fog(const Vector3D & color, const Vector3D& colorFog, float attenuation, float distance, float distMin, float distMax) const
{
    // Fog quadratique
    if (distance < distMin)
        return color;

    if (distance < distMax)
    {
        float coeff = MathUtils::fonctionQuadratique(distMin, distMax, distance) * attenuation;
        return color * (1-coeff) + colorFog * coeff;
    }
    return (1.0 - attenuation) * color + attenuation * colorFog;

    // Fog exponentiel
    /*float fact=10000;
    float att=expf(-(distance-distMin)/fact);
    MathUtils::clamp(0,1,att);
    return att*color+(1-att)*colorFog;*/
}

Vector3D Camera::skyShading(const Sky& sky, const Vector3D& inter, const Terrain* t, const Vector3D& aBox, const Vector3D& bBox, double pMax) const
{
    Ray raySphere(inter ,inter);
    Vector3D inter2;
    bool isBox=false;

    Vector3D lux(0,0,0);
    Vector3D luxRecu(0,0,0);
    Vector3D up(0,0,1);
    Vector3D tmp;
    for(int i = 0; i < sphereSamples.size(); ++i) {
        if(up*sphereSamples[i] > 0) {
            raySphere.origine=inter+1*sphereSamples[i];
            raySphere.direction=sphereSamples[i];
            tmp = sky.getLight(-sphereSamples[i]);
            lux += tmp;
            if(!t->intersectAdvancedMax(raySphere,aBox,bBox,pMax,inter2,isBox,100000))
                luxRecu += tmp;
        }
    }

    luxRecu /= lux.length();
    return luxRecu;
}


QRgb colorSky(const Sky& sky, const Ray & ray)
{

    Vector3D col=sky.getColorLight(-ray.direction);

    return col.toQColor().rgba();
}

Vector3D Camera::shadingCanyon(const Vector3D &inter, const Vector3D &normale, const Sky& sky, const Terrain* t, const Vector3D& aBox, const Vector3D& bBox, const double pMax) const
{
    Vector3D up(0,0,1);
    Vector3D bas(0.98, 0.9, 0.63);
    Vector3D roche(0.9, 0.66, 0.426);
    Vector3D rocheSombre(0.715, 0.48, 0.30);

    double valColorBas = raw_noise_2d(inter.x()/3, inter.y()/3);
    bas = 0.95 * bas + 0.05 * Vector3D(valColorBas, valColorBas, valColorBas);

    double intery=inter.z();
    intery+=-5+10*raw_noise_2d(inter.x()/80,inter.y()/80);

    float crossUp = 1-std::abs(up*normale);

    float angle = acos(crossUp);
    crossUp = angle/M_PI*2;
    crossUp = (1-crossUp)*8;

    float noise1, noise2;
    noise1 = -3+6*raw_noise_2d(inter.x()/30, inter.y()/30);
    noise2 = -1+2*raw_noise_2d(inter.y()/10,inter.x()/10);

    float coefNoise = raw_noise_2d((inter.z()+noise1+noise2)/20, (inter.z()+noise1+noise2)/20);

    float noiseGrisRoche = -0.05+0.1*raw_noise_2d(inter.x()/2, inter.y()/2);
    roche = mix(roche, rocheSombre, coefNoise*coefNoise) + Vector3D(noiseGrisRoche, noiseGrisRoche, noiseGrisRoche);

    Vector3D col=mix(bas, roche, crossUp*crossUp*crossUp);

    Vector3D luxRecu = skyShading(sky, inter, t, aBox, bBox, pMax);
    Vector3D colF = 0.25 * luxRecu + 0.5 * col;
    colF += .25 * diffuse(sky, normale, col);
    colF *= ambientOcclusion(inter, normale, t, aBox, bBox, pMax);

    return colF;
}

Vector3D Camera::shadingMountain(const Vector3D &inter, const Vector3D &normale, const Sky &sky, const Terrain *t, const Vector3D &aBox, const Vector3D &bBox, const double pMax, const Ray& r) const
{

    Vector3D up(0,0,1);

    Vector3D bas(0.29, 0.38, 0.3);
    Vector3D mil(0.36, 0.294, 0.22);
    Vector3D roche(0.75, 0.73, 0.71);
    Vector3D rocheSombre(0.55, 0.53, 0.51);
    Vector3D hau(1, 1, 1);

    double valColorBas = raw_noise_2d(inter.x()/10, inter.y()/10);
    double valColorMil = raw_noise_2d((inter.x()+150)/10, (inter.y()+25)/10);
    bas = 0.95 * bas + 0.05 * Vector3D(valColorBas, valColorBas, valColorBas);
    mil = 0.95 * mil + 0.05 * Vector3D(valColorMil, valColorMil, valColorMil);

    double intery=inter.z();
    intery+=-5+10*raw_noise_2d(inter.x()/80,inter.y()/80);

    float crossUp = 1-std::abs(up*normale);

    float angle = acos(crossUp);
    crossUp = angle/M_PI*2;
    crossUp = (1-crossUp)*8;//*crossUp;//*crossUp);
    float noise1, noise2;
    noise1 = -3+6*raw_noise_2d(inter.x()/30, inter.y()/30);
    noise2 = -1+2*raw_noise_2d(inter.y()/10,inter.x()/10);
    float coefNoise = raw_noise_2d((inter.z()+noise1+noise2)/20, (inter.z()+noise1+noise2)/20);
    float noiseGrisRoche = -0.025+0.05*raw_noise_2d(inter.x()/2, inter.y()/2);
    roche = mix(roche, rocheSombre, coefNoise*coefNoise) + Vector3D(noiseGrisRoche, noiseGrisRoche, noiseGrisRoche);
    Vector3D col;
    if(intery<80){
        col=mix(bas,mil,intery/(80*2));
        col=mix(col, roche, crossUp*crossUp*crossUp);
    }
    else{
        col=mix(mil, roche, crossUp*crossUp*crossUp);
        col = mix(col, hau, (intery-(80*2))/(20*2));
    }

    Vector3D luxRecu = skyShading(sky, inter, t, aBox, bBox, pMax);
    Vector3D colF = 0.2 * luxRecu + 0.4 * col;
    colF += 0.2 * diffuse(sky, normale, col);
    colF += 0.2 * specular(sky, normale, -r.direction,Vector3D(1,1,1), 8);
    colF *= ambientOcclusion(inter, normale, t, aBox, bBox, pMax);
    return colF;
}

QRgb Camera::ptScreen(Terrain * const t, const Vector3D& aBox, const Vector3D& bBox, const Sky& sky, int i, int j, int l, int h,double pMax) const
{
    double x=i*2*lw/l-lw;
    double y=j*2*lh/h-lh;

    Vector3D pt =origine+(dw*w)+(x*u)+(y*v);
    Vector3D dir(pt-origine);
    dir.normalize();
    Ray r(origine,dir);

    Vector3D inter;
    bool isBox=false;
    //if(!t->intersectRayMarching(r,aBox,bBox,inter,isBox)){
    if(!t->intersectAdvanced(r,aBox,bBox,pMax,inter,isBox)){
        //QColor couleur(255,255,255,0);
        //return couleur.rgba();
        return colorSky(sky,ray);
    }

    Vector3D normale;
    t->getHauteurNormale(Vector2D(inter.x(),inter.y()),normale);
    if(isBox) {
        QColor couleur(0,0,0,255);
        return couleur.rgba();
    }
    Vector3D colShading = shadingCanyon(inter, normale, sky, t, aBox, bBox, pMax);
    float dist = r.origine.distanceToPoint(inter);
    Vector3D foggy = fog(colShading, Vector3D(.8, .8, 1), 0.2, dist, 4000, 6000);
    QColor couleur = colShading.toQColor();
    return couleur.rgba();
}

QImage Camera::printScreen(Terrain * const t, const Vector3D& s, int l, int h) const
{
    double pMax=t->getPenteMax();
    QImage im(l,h,QImage::Format_ARGB32);
    double min=t->getHauteurMin();
    double max=t->getHauteurMax();
    Vector3D aBox(t->getA().x(),t->getA().y(),min);
    Vector3D bBox(t->getB().x(),t->getB().y(),max*1.5);

    Sky sky(-s, 0.0);
    #pragma omp parallel for schedule(dynamic)
    for(int i=0;i<l;++i){
        for(int j=0;j<h;++j){
            im.setPixel(l-1-i,h-1-j,ptScreen(t,aBox,bBox,sky,i,j,l,h,pMax));
        }
    }

    return im;

}

void Camera::translate(const Vector3D &v)
{
    origine+=v;
}

