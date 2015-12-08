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

QColor clamp(QColor light)
{
    int r = (int)MathUtils::clamp(0,255, light.red());
    int g = (int)MathUtils::clamp(0,255, light.green());
    int b = (int)MathUtils::clamp(0,255, light.blue());
    return QColor(r,g,b,0);
}

QColor Sky::getLight(Vector3D direction)
{
    direction.normalize();
    float red = 255*nuage + 255 * (1-nuage) * (dirSol*direction);
    float green = 255*nuage + 255 * (1-nuage) * (dirSol*direction);
    float blue = 255*nuage + 255 * (1-nuage) * (dirSol*direction);

    QColor light(red, green, blue);

    return clamp(light);
}
