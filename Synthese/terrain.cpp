#include "terrain.h"
#include <iostream>
Terrain::Terrain(const Vector2D &aa, const Vector2D &bb):penteMax(-1),a(aa),b(bb)
{

}

Vector3D Terrain::norm(const Vector2D &p) const
{
    Vector2D px(p.x()+epsilon,p.y());
    Vector2D pxminus(p.x()-epsilon, p.y());
    Vector2D py(p.x(),p.y()+epsilon);
    Vector2D pyminus(p.x(),p.y()-epsilon);

    double hpx=getHauteur(px);
    double hpxminus = getHauteur(pxminus);
    double hpy=getHauteur(py);
    double hpyminus = getHauteur(pyminus);
    Vector3D resu(-(hpx-hpxminus),-(hpy-hpyminus),2*epsilon);
    resu.normalize();
    return resu;


}


bool Terrain::isIn(const Vector3D &p) const
{
    Vector2D p2(p.x(),p.y());
    return p.z()<=getHauteur(p2);
}

bool Terrain::isOut(const Vector3D &p) const
{
    Vector2D p2(p.x(),p.y());
    return p.z()>getHauteur(p2);
}

double Terrain::getHauteurNormale(const Vector2D &p, Vector3D &n) const
{
    n=norm(p);
    double resu=getHauteur(p);
    return resu;
}


bool Terrain::intersectRayMarching(const Ray& ray, const Vector3D &aBox, const Vector3D &bBox, Vector3D& resu, bool& isBox)
{
    isBox=false;
    resu=ray.origine;

    Vector3D in;
    Vector3D out;

    int pointsBox = ray.intersectsBox(aBox, bBox, in, out);

    if(pointsBox == 0) {
        return false;
    }
    double distInOut = in.distanceToPoint(out);
    Vector3D dir=ray.direction;
    Ray r(in,dir);

    for(double tt = 0; tt <= distInOut+pas; tt+= pas)
    {
        if(isIn(r.getPoint(tt))){

            resu=r.getPoint(tt-pas/2);
            if(tt==0){
                isBox=true;
            }
            return true;
         }

    }

    return false;
}

inline double max(double a,double b)
{
    return a>b?a:b;
}

bool Terrain::intersectAdvancedMax(const Ray &ray, const Vector3D &aBox, const Vector3D &bBox,double pMax, Vector3D &resu, bool& isBox, float distMax) const
{
    double step=pas;
    isBox=false;
    resu=ray.origine;

    Vector3D in;
    Vector3D out;

    int pointsBox = ray.intersectsBox(aBox, bBox, in, out);

    if(pointsBox == 0) {
        return false;
    }
    double distInOut = in.distanceToPoint(out);
    Vector3D dir=ray.direction;
    Ray r(in,dir);
    for(double tt = 0; tt <= distInOut+pas; tt+= step)
    {
        if(tt >= distMax)
            return false;
        Vector3D pointTemp=r.getPoint(tt);
        double dz=pointTemp.z()-getHauteur(Vector2D(pointTemp.x(),pointTemp.y()));
        if(dz<=0){

            resu=r.getPoint(tt-pas/2);
            if(tt==0){
                isBox=true;
            }
            return true;
         }

        step=max(pas,dz/pMax);
    }

    return false;
}


bool Terrain::intersectAdvanced(const Ray &ray, const Vector3D &aBox, const Vector3D &bBox,double pMax, Vector3D &resu, bool& isBox) const
{
    double step=pas;
    isBox=false;
    resu=ray.origine;

    Vector3D in;
    Vector3D out;

    int pointsBox = ray.intersectsBox(aBox, bBox, in, out);

    if(pointsBox == 0) {
        return false;
    }
    double distInOut = in.distanceToPoint(out);
    Vector3D dir=ray.direction;
    Ray r(in,dir);
    for(double tt = 0; tt <= distInOut+pas; tt+= step)
    {
        Vector3D pointTemp=r.getPoint(tt);
        double dz=pointTemp.z()-getHauteur(Vector2D(pointTemp.x(),pointTemp.y()));
        if(dz<=0){

            resu=r.getPoint(tt-pas/2);
            if(tt==0){
                isBox=true;
            }
            return true;
         }

        step=max(pas,dz/pMax);
    }

    return false;
}

double Terrain::epsilon=0.0000001;
double Terrain::pas=0.1;
