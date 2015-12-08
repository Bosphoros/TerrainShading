#include "matrix3.h"

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
               mat(i,j) += m1(i,k)*m2(k,j);
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
            result(i) += m(i,j) * v(i);
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
    Matrix3 mat = Matrix3();
    mat.values[0] = 1;
    mat.values[1] = 0;
    mat.values[2] = 0;
    mat.values[3] = 0;
    mat.values[4] = cos(angle);
    mat.values[5] = -sin(angle);
    mat.values[6] = 0;
    mat.values[7] = sin(angle);
    mat.values[8] = cos(angle);
    return mat;
}

Matrix3 Matrix3::rotateY(float angle)
{
    Matrix3 mat = Matrix3();
    mat.values[0] = cos(angle);
    mat.values[1] = 0;
    mat.values[2] = sin(angle);
    mat.values[3] = 0;
    mat.values[4] = 1;
    mat.values[5] = 0;
    mat.values[6] = -sin(angle);
    mat.values[7] = 0;
    mat.values[8] = cos(angle);
    return mat;
}

Matrix3 Matrix3::rotateZ(float angle)
{
    Matrix3 mat = Matrix3();
    mat.values[0] = cos(angle);
    mat.values[1] = -sin(angle);
    mat.values[2] = 0;
    mat.values[3] = sin(angle);
    mat.values[4] = cos(angle);
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
