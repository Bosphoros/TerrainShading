#include "vector3d.h"
#include "mathutils.h"
#include "matrix3.h"
#include <cmath>

# define M_PI           3.14159265358979323846

#ifndef dabs
    #define dabs(x) x>0?x:-x
#endif

Vector3D::Vector3D(const Vector2D &vector):xp(vector.x()), yp(vector.y()), zp(0.0){}

Vector3D::Vector3D(const Vector2D &vector, double zpos):xp(vector.x()), yp(vector.y()), zp(zpos){}

void Vector3D::rotate(const QMatrix3x3 &mat)
{
    double xt=x()*mat(0,0)+y()*mat(0,1)+z()*mat(0,2);
    double yt=x()*mat(1,0)+y()*mat(1,1)+z()*mat(1,2);
    double zt=x()*mat(2,0)+y()*mat(2,1)+z()*mat(2,2);
    setX(xt);
    setY(yt);
    setZ(zt);
}

Vector3D Vector3D::normal(const Vector3D &v1, const Vector3D &v2)
{
    return (v1^v2).normalized();
}

Vector3D Vector3D::normal(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3)
{
    Vector3D a=v2-v1;
    Vector3D b=v3-v1;
    return (a^b).normalized();
}

double Vector3D::distanceToPlane(const Vector3D &plane, const Vector3D &normal) const
{
    double d=-(plane*normal);
    double num=dabs((*this)*(normal)+d);
    return num/normal.length();

}

double Vector3D::distanceToPlane(const Vector3D &plane1, const Vector3D &plane2, const Vector3D &plane3) const
{
    Vector3D normal = Vector3D::normal(plane1,plane2,plane3);
    return distanceToPlane(plane1, normal);
}

double Vector3D::distanceToLine(const Vector3D &point, const Vector3D &direction) const
{
   double t= (point*direction-(*this)*direction)/(direction*direction);
   return distanceToPoint(point+t*direction);
}


QList<Vector3D> Vector3D::rotateScaleTranslate(QList<Vector3D> points, Vector3D center, float radius, Vector3D normal)
{

    Matrix3 matcam;
        matcam(0,0)=cos(M_PI/2.52);
        matcam(0,1)=0;
        matcam(0,2)=sin(M_PI/2.52);
        matcam(1,0)=0;
        matcam(1,1)=1;
        matcam(1,2)=0;
        matcam(2,0)=-sin(M_PI/2.52);
        matcam(2,1)=0;
        matcam(2,2)=cos(M_PI/2.52);

    QList<Vector3D> newPoints;

    Matrix3 rotate = Matrix3::rotateAtoB(Vector3D(0,1,0), normal);

    for(int i = 0; i < points.size(); i++)
    {
        newPoints << matcam * (center + points[i]*radius);
    }
    return newPoints;
}

QList<Vector3D> Vector3D::randHemisphere(int nbPoints)
{
    QList<Vector3D> points;
    float rCarre = 1.0/(float)nbPoints;

    for(int j=0;j<nbPoints*50;++j){

        float phi = MathUtils::random(0, 2*M_PI);
        float theta = MathUtils::random(-M_PI/2, M_PI/2);

        float x = std::cos(phi) * std::sin(theta);
        float y = std::sin(phi) * std::sin(theta);
        float z = std::cos(theta);

        Vector3D pointTemp (x,z ,y);

        bool b=true;


        for(int i=0;i<points.size();++i){
            if(pointTemp.distanceToPointSquared(points[i])<4*rCarre){
                //goto continue_tag;
                b=false;
                break;
            }

        }
        //points<<pointTemp;

        if(b){
            points<<pointTemp;
        }

        //continue_tag:;

    }

    return points;
}











