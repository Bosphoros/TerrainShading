#ifndef RAY_H
#define RAY_H
#include "vector3d.h"
/**
 * @brief The Ray class
 */
class Ray
{
private:
    static double pas;/**< The length used for Ray Marching of the Terrains*/
public:
    const Vector3D origine; /**< The origin of the Ray*/
    const Vector3D direction;/**< The direction of the Ray, normalized*/

    /**
     * Constructor of a Ray
     * @param[in] o the origin of the Ray
     * @param[in] d the direction of the Ray, is normalized by the constructor
     */
    Ray(const Vector3D &o, const Vector3D &d);

    /**
     * Gets the point corresponding to f times the direction vector from the origin, is inlined
     * @param[in] f the factor of the direction vector
     * @return origine + f * direction
     */
    Vector3D getPoint(double f) const;

    /**
     * Tries to intersect the Ray with a plane, described by two vectors, ab and ac
     * @param[in] a the first point on the plane
     * @param[in] b the second point on the plane
     * @param[in] c the third point on the plane
     * @param[out] out the point at the intersection of the Ray and the plane
     * @return true if the Ray intersects the plane, false else
     */
    bool intersects(const Vector3D& a, const Vector3D& b, const Vector3D& c, Vector3D& out) const;

    /**
     * Counts the intersections of the Ray with a box
     * @param[in] a the first corner describing the box
     * @param[in] b the second corner describing the box
     * @param[out] in the point on the box where the Ray enters
     * @param[out] out the point on the box where the Ray exits
     * @see intersects()
     * @return the number of intersections of the ray with the box. If 1, in will be the origin of the Ray and out the only intersection. If 0, do not consider in and out are reliable.
     */
    int intersectsBox(const Vector3D& a, const Vector3D& b, Vector3D& in, Vector3D& out) const;

};

    inline Vector3D Ray::getPoint(double f) const{
        return origine+direction*f;
    }

#endif // RAY_H
