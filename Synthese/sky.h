#ifndef SKY_H
#define SKY_H
#include "vector3d.h"
#include <QColor>

class Sky
{
private :
    Vector3D dirSol;
    float nuage;

public:
    Sky();
    Sky(Vector3D dir, float n) : dirSol(dir.normalized()), nuage(n) {}
    Vector3D getLight(Vector3D direction) const;
    Vector3D getDirSol() const;
    void setDirSol(const Vector3D &value);
    float getNuage() const;
    void setNuage(float value);
};

#endif // SKY_H
