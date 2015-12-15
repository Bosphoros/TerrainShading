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

float Camera::ambientOcclusion(const Vector3D& inter, const Vector3D& normale, Terrain* t, const Vector3D& aBox, const Vector3D& bBox, double pMax) const
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

Vector3D fog(const Vector3D & color, float distance, float distMin, float distMax)
{
    if (distance < distMin)
        return color;

    Vector3D colorFog = Vector3D(0,0,255);
    float attenuation = 0.2f;

    if (distance < distMax)
    {
        float coeff = MathUtils::fonctionQuadratique(distMin, distMax, distance) * attenuation;
        return color * (1-coeff) + colorFog * coeff;
    }
    return (1.0 - attenuation) * color + attenuation * colorFog;
}

Vector3D Camera::skyShading(const Sky& sky, const Vector3D& inter, Terrain* t, const Vector3D& aBox, const Vector3D& bBox, double pMax) const
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
        QColor couleur(255,255,255,0);
        return couleur.rgba();
    }

    Vector3D normale;
    t->getHauteurNormale(Vector2D(inter.x(),inter.y()),normale);
    if(isBox) {
        QColor couleur(0,0,0,255);
        return couleur.rgba();
    }

    Vector3D up(0,0,1);

    Vector3D bas(74,97,77);
    Vector3D mil(91,75,55);
    Vector3D roche(190,185,180);
    Vector3D rocheSombre(140,135,130);
    Vector3D hau(255,255,255);
    Vector3D col(255,255,255);

    rocheSombre = Vector3D::product(rocheSombre, Vector3D(1.3,.9,.6));
    roche = Vector3D::product(roche, Vector3D(1.2,.9,.6));
    bas = Vector3D(255, 255, 220);

    double valColorBas = raw_noise_2d(inter.x()/10, inter.y()/10);
    double valColorMil = raw_noise_2d((inter.x()+150)/10, (inter.y()+25)/10);
    bas = 0.95 * bas + 0.05 * Vector3D(valColorBas * 255, valColorBas * 255, valColorBas * 255);
    mil = 0.95 * mil + 0.05 * Vector3D(valColorMil * 255, valColorMil * 255, valColorMil * 255);

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
    float noiseGrisRoche = -5+10*raw_noise_2d(inter.x()/10, inter.y()/10);
    roche = mix(roche, rocheSombre, coefNoise*coefNoise) + Vector3D(noiseGrisRoche, noiseGrisRoche, noiseGrisRoche);
    if(intery<80){
        col=mix(bas,mil,intery/(80*2));
        col=mix(col, roche, crossUp*crossUp*crossUp);
    }
    else{
        col=mix(mil, roche, crossUp*crossUp*crossUp);
        col = mix(col, hau, (intery-(80*2))/(20*2));
    }

    //col = Vector3D(1,1,1);
    Vector3D luxRecu = skyShading(sky, inter, t, aBox, bBox, pMax);
    Vector3D colF = 0.5 * Vector3D::product(col/255,luxRecu);
    colF *= ambientOcclusion(inter, normale, t, aBox, bBox, pMax);
    colF += 0.5 * diffuse(sky, normale, col/255);
    //colF += 0.2 * specular(sky, normale, -r.direction,Vector3D(1,1,1), 8);
    //std::cout << col << std::endl;
    QColor couleur = colF.toQColor();
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

