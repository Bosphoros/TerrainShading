#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "vector2d.h"
#include <cmath>
#include <iostream>
#include <QMatrix3x3>

class Vector2D;
/**
 * @brief The Vector3D class
 */
class Vector3D
{
public:
    /**
     * Default constructor, initializes xp, yp and zp to 0
     */
    Vector3D();
    /**
     * Constructor of Vector3D
     * @param[in] xpos the x position of the vector
     * @param[in] ypos the y position of the vector
     * @param[in] zpos the z position of the vector
     */
    Vector3D(double xpos, double ypos, double zpos):xp(xpos), yp(ypos), zp(zpos){}
    /**
     * Constructor of Vector3D from a Vector2D, zp set to 0
     * @param[in] vector the Vector2D to base the xp and yp coordinates on
     */
    Vector3D(const Vector2D& vector);
    /**
     * Constructor of Vector3D from a Vector2D
     * @param[in] vector the Vector2D to base the xp and yp coordinates on
     * @param[in] zpos the z position of the vector
     */
    Vector3D(const Vector2D& vector, double zpos);

    /**
     * @brief Return the x value of the vector
     * @return the x value of the vector
     */
    double x() const;
    /**
     * @brief Return the y value of the vector
     * @return the y value of the vector
     */
    double y() const;
    /**
     * @brief Return the z value of the vector
     * @return the z value of the vector
     */
    double z() const;

    /**
     * Sets the value of xp
     * @param[in] xpos the new value of xp
     */
    void setX(double xpos);
    /**
     * Sets the value of yp
     * @param[in] ypos the new value of yp
     */
    void setY(double ypos);
    /**
     * Sets the value of zp
     * @param[in] zpos the new value of zp
     */
    void setZ(double zpos);

    /**
     * Returns the length of the vector. Uses a square root
     * @return the length of the vector
     */
    double length() const;
    /**
     * Returns the squared length of the vector
     * @return the squared length of the vector
     */
    double lengthSquared() const;

    /**
     * Returns the normalized vector
     * @return a new Vector2D corresponding to the normalized vector
     */
    Vector3D normalized() const;
    /**
     * Normalizes the vector
     */
    void normalize();

    /**
     * Adds a vector to this vector and returns its reference
     * @param[in] vector the vector to add
     * @return a reference to the vector
     */

    void rotate(const QMatrix3x3 &mat);

    Vector3D &operator+=(const Vector3D &vector);
    /**
     * Substracts a vector to this vector and returns its reference
     * @param[in] vector the vector to substract
     * @return a reference to the vector
     */
    Vector3D &operator-=(const Vector3D &vector);
    /**
     * Multiplies the vector by a factor and returns its reference
     * @param[in] factor the factor to multiply by
     * @return a reference to the vector
     */
    Vector3D &operator*=(double factor);
    /**
     * Divides the vector by a divisor and returns its reference
     * @param[in] divisor the divisor to divide by
     * @return a reference to the vector
     */
    Vector3D &operator/=(double divisor);
    /**
     * Dot product of the vector and another one
     * @param[in] v1 the other vector for the dot product
     * @return the value of the dot product of the two vectors
     */
    double operator*(const Vector3D& v1) const;
    /**
     * Cross product of the vector and another one
     * @param[in] v2 the other vector for the cross product
     * @return the Vector3D resulting from the cross product
     */
    const Vector3D operator^(const Vector3D& v2)const ;

    /**
     * Read-access to the i-th member of the vector
     * @param i the number of the member
     * @return
     */
    double operator()(int i) const;

    /**
     * Write-access to the i-th member of the vector
     * @param i the number of the member
     * @return
     */
    double& operator()(int i);

    /**
     * Returns the normal of the plane described by the two vectors
     * @param[in] v1 the first vector describing the plane
     * @param[in] v2 the second vector describing the plane
     * @return a Vector3D representing the normal
     */
    static Vector3D normal(const Vector3D& v1, const Vector3D& v2);
    /**
     * Returns the normal of the plane described by the three points
     * @param[in] v1 the first point
     * @param[in] v2 the second point
     * @param[in] v3 the third point
     * @return a Vector3D representing the normal
     */
    static Vector3D normal(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    /**
     * Returns the distance between the point represented by the vector and another point. Uses a square root
     * @param[in] point the point we want the distance to
     * @return the distance between the two points
     */
    double distanceToPoint(const Vector3D& point) const;
    /**
     * Returns the square of the distance between the point represented by the vector and another point
     * @param[in] point the point we want the distance to
     * @return the square of the distance between the two points
     */
    double distanceToPointSquared(const Vector3D& point) const;
    /**
     * Returns the shortest distance between the 3D point and a plane represented by a point and a normal
     * @param[in] plane the point on the plane
     * @param[in] normal the normal of the plane
     * @return the shortest distance between the point and the plane
     */
    double distanceToPlane(const Vector3D& plane, const Vector3D& normal) const;
    /**
     * Returns the shortest distance between the 3D point and a plane described by three points
     * @param[in] plane1 the first point on the plane
     * @param[in] plane2 the second point on the plane
     * @param[in] plane3 he third point on the plane
     * @return the shortest distance between the point and the plane
     */
    double distanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const;
    /**
     * Returns the shortest distance between the 3D point and a line
     * @param[in] point a point on the line
     * @param[in] direction the direction of the line
     * @return the shortest distance between the 3D point and the line
     */
    double distanceToLine(const Vector3D& point, const Vector3D& direction) const;

    /**
     * Checks if the coordinates of the two vectors are strictly equal
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the coordinates xp and yp of the vectors are equals, else false
     */
    friend inline bool operator==(const Vector3D &v1, const Vector3D &v2);
    /**
     * Checks if the coordinates of the two vectors are not strictly equal
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the coordinates xp and yp of the vectors are not equals, else false
     */
    friend inline bool operator!=(const Vector3D &v1, const Vector3D &v2);
    /**
     * Adds two vectors and returns the result of the addition
     * @param[in] v1 the first vector to add
     * @param[in] v2 the second vector to add
     * @return a new Vector3D resulting of the addition of the two others
     */
    friend inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
    /**
     * Substracts a vector to the other and returns the result of the addition
     * @param[in] v1 the first vector to be substracted
     * @param[in] v2 the second vector to substract
     * @return a new Vector3D resulting of the substraction
     */
    friend inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
    /**
     * Multiplies a vector by a factor and returns the result of the multiplication
     * @param[in] factor the factor to multiply by
     * @param[in] vector the vector to multiply
     * @return a new Vector3D resulting of the multiplication
     */
    friend inline const Vector3D operator*(double factor, const Vector3D &vector);
    /**
     * Multiplies a vector by a factor and returns the result of the multiplication
     * @param[in] vector the vector to multiply
     * @param[in] factor the factor to multiply by
     * @return a new Vector3D resulting of the multiplication
     */
    friend inline const Vector3D operator*(const Vector3D &vector, double factor);
    /**
     * Reverses the coordinates of the vector
     * @param[in] vector the vector to reverse
     * @return a new Vector3D resulting of the reversing
     */
    friend inline const Vector3D operator-(const Vector3D &vector);
    /**
     * Divides a vector by a divisor and returns the result of the division
     * @param[in] vector the vector to divide
     * @param[in] divisor the divisor to divide by
     * @return a new Vector3D resulting of the division
     */
    friend inline const Vector3D operator/(const Vector3D &vector, double divisor);

    /**
     * Compares the coordinates of the two vectors, allowing a small difference
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the vectors are at worst slightly different, else false
     */
    friend inline bool fuzzyCompare(const Vector3D& v1, const Vector3D& v2);
    /**
     * Prints the coordinates of the vector in the ostream
     * @param[in] out the stream to write in
     * @param[in] v the vector to write in the stream
     * @return a reference to the stream
     */
    friend inline std::ostream& operator<<(std::ostream& out, const Vector3D& v);

    static QList<Vector3D> rotateScaleTranslate(QList<Vector3D> points, Vector3D center, float radius, Vector3D normal);
    static QList<Vector3D> randHemisphere(int nbPoints);

private:
    double xp; /**< The x coordinate of the vector */
    double yp; /**< The y coordinate of the vector */
    double zp; /**< The z coordinate of the vector */
};


inline Vector3D::Vector3D() : xp(0.0), yp(0.0), zp(0.0) {}

inline double Vector3D::x() const { return xp; }
inline double Vector3D::y() const { return yp; }
inline double Vector3D::z() const { return zp; }

inline void Vector3D::setX(double aX) { xp = aX; }
inline void Vector3D::setY(double aY) { yp = aY; }
inline void Vector3D::setZ(double aZ) { zp = aZ; }

inline Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    return *this;
}

inline Vector3D &Vector3D::operator/=(double factor)
{
    xp /= factor;
    yp /= factor;
    zp /= factor;
    return *this;
}

inline bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp;
}

inline bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp;
}

inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp);
}

inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp);
}

inline const Vector3D operator*(double factor, const Vector3D &vector)
{
    return Vector3D(vector.x() * factor, vector.y() * factor, vector.z() * factor);
}

inline const Vector3D operator*(const Vector3D &vector, double factor)
{
    return Vector3D(vector.x() * factor, vector.y() * factor, vector.z() * factor);
}

inline double Vector3D::operator*(const Vector3D &v1) const
{
    return xp * v1.x()+ yp * v1.y()+ zp * v1.z();
}

inline const Vector3D Vector3D::operator^(const Vector3D &v1) const
{
    return Vector3D(yp*v1.z()-zp*v1.y(),zp*v1.x()-xp*v1.z(),xp*v1.y()-yp*v1.x());
}


inline double Vector3D::operator()(int i) const {
    if(i == 0)
        return xp;
    if(i == 1)
        return yp;
    return zp;
}

inline double& Vector3D::operator()(int i) {
    if(i == 0)
        return xp;
    if(i == 1)
        return yp;
    return zp;
}

inline const Vector3D operator-(const Vector3D &vector)
{
    return Vector3D(-vector.xp, -vector.yp, -vector.zp);
}

inline const Vector3D operator/(const Vector3D &vector, double divisor)
{
    return Vector3D(vector.x() / divisor, vector.y() / divisor, vector.z() / divisor);
}

inline bool fuzzyCompare(const Vector3D& v1, const Vector3D& v2)
{
    return v1.distanceToPointSquared(v2)<0.0000001;
}

inline double Vector3D::length() const
{
    return sqrt(xp*xp+yp*yp+zp*zp);
}
inline double Vector3D::lengthSquared() const
{
    return xp*xp+yp*yp+zp*zp;
}

inline Vector3D Vector3D::normalized() const
{
    double invlength =1/length();

    return Vector3D(xp*invlength,yp*invlength,zp*invlength);
}
inline void Vector3D::normalize()
{
    double invlength =1/length();
    xp*=invlength;
    yp*=invlength;
    zp*=invlength;
}

inline double Vector3D::distanceToPoint(const Vector3D& point) const
{
    return (point-(*this)).length();
}

inline double Vector3D::distanceToPointSquared(const Vector3D& point) const
{
    return (point-(*this)).lengthSquared();
}

inline std::ostream& operator<<(std::ostream& out, const Vector3D& v){
    return out<<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<")";
}


#endif // VECTOR3D_H

