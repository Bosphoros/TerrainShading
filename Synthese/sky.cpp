#include "sky.h"
#include "mathutils.h"

Vector3D Sky::getDirSol() const
{
    return dirSol;
}

void Sky::setDirSol(const Vector3D &value)
{
    dirSol = value;
}

float Sky::getNuage() const
{
    return nuage;
}

void Sky::setNuage(float value)
{
    nuage = value;
}

Sky::Sky()
{

}

Vector3D clamp(Vector3D light)
{
    float r = MathUtils::clamp(0,1, light.x());
    float g = MathUtils::clamp(0,1, light.y());
    float b = MathUtils::clamp(0,1, light.z());
    return Vector3D(r,g,b);
}

Vector3D mixColor(const Vector3D& a,const Vector3D& b, double d){
    double quadra=MathUtils::fonctionQuadratique(0,1,d);
    return b*quadra+a*(1-quadra);
}

Vector3D Sky::getLight(Vector3D direction) const
{
    direction.normalize();
    /*Vector3D jaune(1,1,0.8);
    Vector3D bleu(0.8,0.9,1);*/
    Vector3D gris(.9,.9,.9);
    Vector3D white(1,1,1);
    Vector3D light=mixColor(gris,white,nuage + (1-nuage) * (dirSol*direction));
    /*float red =nuage + (1-nuage) * (dirSol*direction)*(dirSol*direction)*(dirSol*direction);
    float green = nuage + (1-nuage) * (dirSol*direction) * (dirSol*direction)* (dirSol*direction);
    float blue =nuage + (1-nuage) * (dirSol*direction);*/

    //Vector3D light(red, green, blue*0.3);

    return clamp(light);
}
