#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>
#include "vector3d.h"

class Vector3D;
/**
 * @brief The Vector2D class
 */
class Vector2D
{
private:
    double xp; /**< The x coordinate of the vector */
    double yp; /**< The y coordinate of the vector */
public:
    /**
     * Default constructor, initializes xp and yp to 0
     */
    Vector2D();

    /**
     * Constructor of Vector2D
     * @param[in] xpos the x position of the vector
     * @param[in] ypos the y position of the vector
     */
    Vector2D(double xpos, double ypos);

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
     * Sets the value of xp
     * @param[in] x the new value of xp
     */
    void setX(double x);
    /**
     * Sets the value of yp
     * @param[in] y the new value of yp
     */
    void setY(double y);

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
    Vector2D normalized() const;
    /**
     * Normalizes the vector
     */
    void normalize();

    /**
     * Returns the distance between the point represented by the vector and another point. Uses a square root
     * @param[in] point the point we want the distance to
     * @return the distance between the two points
     */
    double distanceToPoint2D(const Vector2D& point) const;
    /**
     * Returns the square of the distance between the point represented by the vector and another point
     * @param[in] point the point we want the distance to
     * @return the square of the distance between the two points
     */
    double distanceToPoint2DSquared(const Vector2D& point) const;
    /**
     * Returns the shortest distance between the 2D point and a line
     * @param[in] point a point on the line
     * @param[in] direction the direction of the line
     * @return the shortest distance between the 2D point and the line
     */
    double distanceToLine(const Vector2D& point, const Vector2D& direction) const;

    /**
     * Adds a vector to this vector and returns its reference
     * @param[in] vector the vector to add
     * @return a reference to the vector
     */
    Vector2D &operator+=(const Vector2D& vector);
    /**
     * Substracts a vector to this vector and returns its reference
     * @param[in] vector the vector to substract
     * @return a reference to the vector
     */
    Vector2D &operator-=(const Vector2D& vector);
    /**
     * Multiplies the vector by a factor and returns its reference
     * @param[in] factor the factor to multiply by
     * @return a reference to the vector
     */
    Vector2D &operator*=(double factor);
    /**
     * Divides the vector by a divisor and returns its reference
     * @param[in] divisor the divisor to divide by
     * @return a reference to the vector
     */
    Vector2D &operator/=(double divisor);

    /**
     * Checks if the coordinates of the two vectors are strictly equal
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the coordinates xp and yp of the vectors are equals, else false
     */
    friend inline bool operator==(const Vector2D& v1, const Vector2D& v2);
    /**
     * Checks if the coordinates of the two vectors are not strictly equal
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the coordinates xp and yp of the vectors are not equals, else false
     */
    friend inline bool operator!=(const Vector2D& v1, const Vector2D& v2);
    /**
     * Adds two vectors and returns the result of the addition
     * @param[in] v1 the first vector to add
     * @param[in] v2 the second vector to add
     * @return a new Vector2D resulting of the addition of the two others
     */
    friend inline const Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
    /**
     * Substracts a vector to the other and returns the result of the addition
     * @param[in] v1 the first vector to be substracted
     * @param[in] v2 the second vector to substract
     * @return a new Vector2D resulting of the substraction
     */
    friend inline const Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
    /**
     * Multiplies a vector by a factor and returns the result of the multiplication
     * @param[in] factor the factor to multiply by
     * @param[in] v2 the vector to multiply
     * @return a new Vector2D resulting of the multiplication
     */
    friend inline const Vector2D operator*(double factor, const Vector2D& v2);
    /**
     * Multiplies a vector by a factor and returns the result of the multiplication
     * @param[in] v1 the vector to multiply
     * @param[in] factor the factor to multiply by
     * @return a new Vector2D resulting of the multiplication
     */
    friend inline const Vector2D operator*(const Vector2D& v1, double factor);
    /**
     * Dot product between the two vectors
     * @param[in] v1 the first vector
     * @param[in] v2 the second vector
     * @return the value of the dot product between the two vectors
     */
    friend inline double operator*(const Vector2D& v1, const Vector2D& v2);
    /**
     * Reverses the coordinates of the vector
     * @param[in] v1 the vector to reverse
     * @return a new Vector2D resulting of the reversing
     */
    friend inline const Vector2D operator-(const Vector2D& v1);
    /**
     * Divides a vector by a divisor and returns the result of the division
     * @param[in] v1 the vector to divide
     * @param[in] divisor the divisor to divide by
     * @return a new Vector2D resulting of the division
     */
    friend inline const Vector2D operator/(const Vector2D& v1, double divisor);

    /**
     * Compares the coordinates of the two vectors, allowing a small difference
     * @param[in] v1 the first vector to compare
     * @param[in] v2 the vector to compare to
     * @return true if the vectors are at worst slightly different, else false
     */
    friend inline bool fuzzyCompare(const Vector2D& v1, const Vector2D& v2);

    /**
     * Prints the coordinates of the vector in the ostream
     * @param[in] os the stream to write in
     * @param[in] v the vector to write in the stream
     * @return a reference to the stream
     */
    friend inline std::ostream& operator<<(std::ostream& os, const Vector2D& v);

    /**
     * Creates a Vector3D having the same xp and yp, and zp to 0
     * @return a new Vector3D, having the same xp and yp, and zp to 0
     */
    Vector3D toVector3D() const;

    friend class Vector3D;
};

inline Vector2D::Vector2D() : xp(0.0d), yp(0.0d) {}

inline Vector2D::Vector2D(double xpos, double ypos) : xp(xpos), yp(ypos) {}

inline double Vector2D::x() const {return xp;}
inline double Vector2D::y() const {return yp;}

inline void Vector2D::setX(double ax) { xp = ax; }
inline void Vector2D::setY(double ay) { yp = ay; }

inline double Vector2D::length() const {
    return sqrt(xp*xp+yp*yp);
}

inline double Vector2D::lengthSquared() const {
    return xp*xp+yp*yp;
}

inline double Vector2D::distanceToPoint2D(const Vector2D& point) const {
    return (point-(*this)).length();
}

inline double Vector2D::distanceToPoint2DSquared(const Vector2D& point) const {
    return (point-(*this)).lengthSquared();
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v) {
    xp += v.xp;
    yp += v.yp;
    return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v) {
    xp -= v.xp;
    yp -= v.yp;
    return *this;
}

inline Vector2D& Vector2D::operator*=(double factor) {
    xp *= factor;
    yp *= factor;
    return *this;
}

inline Vector2D& Vector2D::operator/=(double divisor) {
    xp /= divisor;
    yp /= divisor;
    return *this;
}

inline bool operator==(const Vector2D& v1, const Vector2D& v2) {
    return v1.xp == v2.xp && v1.yp == v2.yp ;
}

inline bool operator!=(const Vector2D& v1, const Vector2D& v2) {
    return v1.xp != v2.xp && v1.yp != v2.yp ;
}

inline const Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.xp + v2.xp , v1.yp + v2.yp);
}

inline const Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.xp - v2.xp , v1.yp - v2.yp);
}

inline const Vector2D operator*(double factor, const Vector2D& v) {
    return Vector2D(v.xp * factor, v.yp * factor);
}

inline const Vector2D operator*(const Vector2D& v, double factor) {
    return Vector2D(v.xp * factor, v.yp * factor);
}

inline double operator*(const Vector2D& v1, const Vector2D& v2) {
    return (v1.xp * v2.xp + v1.yp * v2.yp);
}

inline const Vector2D operator-(const Vector2D& v) {
    return Vector2D(-v.xp, -v.yp);
}

inline const Vector2D operator/(const Vector2D& v, double divisor) {
    return Vector2D(v.xp / divisor, v.yp / divisor);
}

inline bool fuzzyCompare(const Vector2D& v1, const Vector2D& v2) {
    return v1.distanceToPoint2DSquared(v2) < 0.0000001;
}

inline std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    return os << "(" << v.xp << ", " << v.yp << ")";
}


#endif // VECTOR2D_H
