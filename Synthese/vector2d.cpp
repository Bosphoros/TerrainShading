#include "vector2d.h"



Vector2D Vector2D::normalized() const
{
    double invlength = 1/length();
    return (*this)*invlength;
}

void Vector2D::normalize()
{
    double invlength = 1/length();
    (*this)*=invlength;
}

double Vector2D::distanceToLine(const Vector2D &point, const Vector2D &direction) const
{
    double t = -(point*direction-(*this)*direction)/(direction*direction);
    return (*this).distanceToPoint2D(Vector2D(point + t*direction));
}

Vector3D Vector2D::toVector3D() const
{
    return (*this);
}
