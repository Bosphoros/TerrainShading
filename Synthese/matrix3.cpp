#include "matrix3.h"
#define M_PI 3.14159265358979323846
Matrix3::Matrix3()
{
    for (int i = 0; i < 9; i++)
    {
        values[i] = 0;
    }
}

Matrix3::Matrix3(float values[])
{
    for (int i = 0; i < 9; i++)
    {
        this->values[i] = values[i];
    }
}

const Matrix3 operator+(const Matrix3& m1, const Matrix3& m2)
{
    float output[9];
    for (int i = 0; i < 9; i++)
    {
        output[i] = m1.values[i] + m2.values[i];
    }
    return Matrix3(output);
}

const Matrix3 operator-(const Matrix3& m1, const Matrix3& m2)
{
    float output[9];
    for (int i = 0; i < 9; i++)
    {
        output[i] = m1.values[i] - m2.values[i];
    }
    return Matrix3(output);
}

ostream& operator<<(ostream& os, const Matrix3 &m)
{
    for (int i=0; i < 3; i++)
    {
        for (int j=0; j < 3; j++)
        {
            os << m(i,j) << " ";
        }
        os << endl;
    }
    return os;
}

const Matrix3 operator*(const Matrix3& m1, const Matrix3& m2)
{
    Matrix3 mat = Matrix3();
    for(int i=0; i<3; ++i)
    {
       for(int j=0; j<3; ++j)
       {
           for(int k=0; k<3; ++k)
           {
               mat(j,i) += m1(i,k)*m2(k,j);
           }
       }
    }
    return mat;
}

const Vector3D operator*(const Matrix3& m, const Vector3D& v)
{
    Vector3D result;
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            result(i) += m(i,j) * v(j);
        }
    }
    return result;
}

const Matrix3 operator*(const Matrix3& m1, float f)
{
    Matrix3 mat = Matrix3();
    for(int i=0; i<9; ++i)
    {
        mat.values[i] = m1.values[i]*f;
    }
    return mat;
}

const Matrix3 operator*(float f, const Matrix3& m1)
{
    Matrix3 mat = Matrix3();
    for(int i=0; i<9; ++i)
    {
        mat.values[i] = m1.values[i]*f;
    }
    return mat;
}

int Matrix3::determinant() const
{

    return (values[0]*values[4]*values[8] + values[3]*values[7]*values[2] + values[6]*values[1]*values[5])
            -(values[6]*values[4]*values[2] + values[0]*values[7]*values[5] + values[3]*values[1]*values[8]);
}

Matrix3 Matrix3::transpose() const
{
    Matrix3 mat = Matrix3();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat(i,j) = this->values[j+3*i];
        }
    }
    return mat;
}

Matrix3 Matrix3::identity()
{
    float tab[9] = { 1, 0, 0,
                     0, 1, 0,
                     0, 0, 1};
}

Matrix3 Matrix3::rotateX(float angle)
{
    float cos1=cos(angle);
    float sin1=sin(angle);
    Matrix3 mat = Matrix3();
    mat.values[0] = 1;
    mat.values[1] = 0;
    mat.values[2] = 0;
    mat.values[3] = 0;
    mat.values[4] = cos1;
    mat.values[5] = -sin1;
    mat.values[6] = 0;
    mat.values[7] = sin1;
    mat.values[8] = cos1;
    return mat;
}

Matrix3 Matrix3::rotateY(float angle)
{
    float cos1=cos(angle);
    float sin1=sin(angle);
    Matrix3 mat = Matrix3();
    mat.values[0] = cos1;
    mat.values[1] = 0;
    mat.values[2] = sin1;
    mat.values[3] = 0;
    mat.values[4] = 1;
    mat.values[5] = 0;
    mat.values[6] = -sin1;
    mat.values[7] = 0;
    mat.values[8] = cos1;
    return mat;
}

Matrix3 Matrix3::rotateZ(float angle)
{
    float cos1=cos(angle);
    float sin1=sin(angle);
    Matrix3 mat = Matrix3();
    mat.values[0] = cos1;
    mat.values[1] = -sin1;
    mat.values[2] = 0;
    mat.values[3] = sin1;
    mat.values[4] = cos1;
    mat.values[5] = 0;
    mat.values[6] = 0;
    mat.values[7] = 0;
    mat.values[8] = 1;
    return mat;
}

Matrix3 Matrix3::rotateXYZ(float angleX, float angleY, float angleZ)
{
    return rotateX(angleX) * rotateY(angleY) * rotateZ(angleZ);
}

Matrix3 Matrix3::rotateAtoB(const Vector3D &a, const Vector3D &b)
{
    Vector3D v = a ^ b;
    float s = v.lengthSquared();
    float c = a * b;

    float tab[9] = {0, -v.z(), v.y(),
                    v.z(), 0, -v.x(),
                    -v.y(), v.x(), 0};

    Matrix3 mat(tab);

    return identity() + mat + mat*mat*(1-c)*(1.0/s);

}

Matrix3 Matrix3::rotateZtoV(const Vector3D &v)
{
    Vector3D Z(0,0,1);

    float angle = acosf(Z*v);
    Vector3D axe = Z^v;
    axe.normalize();
    float a = axe.x();
    float b = axe.y();
    float c = axe.z();

    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    Matrix3 mat;
    mat(0,0) = a*a+(1-a*a)*cosAngle;
    mat(0,1) = a*b*(1-cosAngle)-c*sinAngle;
    mat(0,2) = a*c*(1-cosAngle)+b*sinAngle;
    mat(1,0) = a*b*(1-cosAngle)+c*sinAngle;
    mat(1,1) = b*b+(1-b*b)*cosAngle;
    mat(1,2) = b*c*(1-cosAngle)-a*sinAngle;
    mat(2,0) = a*c*(1-cosAngle)-b*sinAngle;
    mat(2,1) = b*c*(1-cosAngle)+a*sinAngle;
    mat(2,2) = c*c+(1-c*c)*cosAngle;


     return mat;
}
