#ifndef MATRIX3X3_H
#define MATRIX3X3_H
#include "vector3d.h"
#include <iostream>

using namespace std;

class Matrix3
{
private:
    float values[9];
public:
    inline Matrix3();
    inline Matrix3(float values[]);

    friend const Matrix3 operator+(const Matrix3& m1, const Matrix3& m2);
    friend const Matrix3 operator-(const Matrix3& m1, const Matrix3& m2);
    friend const Matrix3 operator*(const Matrix3& m1, const Matrix3& m2);
    friend const Matrix3 operator*(const Matrix3& m, float f);
    friend const Matrix3 operator*(float f, const Matrix3& m);
    friend const Vector3D operator*(const Matrix3& m, const Vector3D& v);
    friend ostream& operator<<(ostream& os, const Matrix3 &m);

    inline float operator()(int i, int j) const {return values[i*3+j];}
    inline float& operator()(int i, int j) {return values[i+3*j];}

    int determinant() const;
    Matrix3 transpose() const;
    static Matrix3 identity();
    static Matrix3 rotateX(float angle);
    static Matrix3 rotateY(float angle);
    static Matrix3 rotateZ(float angle);
    static Matrix3 rotateXYZ(float angleX, float angleY, float angleZ);
    static Matrix3 rotateAtoB(const Vector3D &a, const Vector3D &b);
};

#endif // MATRIX3X3_H
