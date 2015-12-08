#ifndef TERRAIN_H
#define TERRAIN_H

#include "vector2d.h"
#include "vector3d.h"
#include "ray.h"
/**
 * @brief The Terrain class
 */
class Terrain
{

protected:
    static double epsilon; /**< The precision used for the derivative */

    /**
     * Finds the normal at point p
     * @param[in] p the point containing the coordinates on the Terrain we want the normal of
     * @return
     */
    Vector3D norm(const Vector2D &p) const;
    double penteMax;
    Vector2D a; /**< The first coordinate defining the Terrain */
    Vector2D b; /**< The second coordinate defining the Terrain */
    static double pas;/**< The length used for Ray Marching */

public:
    /**
     * Constructor of Terrain
     * @param[in] aa the first point of definition of the Terrain on the plane
     * @param[in] bb the second point of definition of the Terrain on the plane
     */
    Terrain(const Vector2D& aa, const Vector2D& bb);

    /**
     * Checks if a point is under the surface of the Terrain or not
     * @param[in] p the point to check the position of
     * @return true if is under the surface, else false
     */
    bool isIn(const Vector3D& p) const;

    /**
     * Checks if a point is above the surface of the Terrain or not
     * @param[in] p the point to check the position of
     * @return true if is above the surface, else false
     */
    bool isOut(const Vector3D& p) const;

    /**
     * Calculates the height of a point based on its 2D coordinates and the normal at this point
     * @param[in] p the coordinates to find the corresponding height
     * @param[out] n the normal at p
     * @see getHauteur()
     * @return the height at p
     */
    double getHauteurNormale(const Vector2D& p, Vector3D &n) const;

    /**
     * @brief Gets the height associated to 2D coordinates
     * @param[in] p the coordinates to find the corresponding height
     * @return the height at p
     */
    virtual double getHauteur(const Vector2D& p) const =0;

    /**
     * Finds the minimal height of the Terrain
     * @return the minimal height of the Terrain
     */
    virtual double getHauteurMin() const =0;

    /**
     * Finds the maximal height of the Terrain
     * @return the maximal height of the Terrain
     */
    virtual double getHauteurMax() const =0;

    /**
     * Finds the greatest difference of height between two points
     * @return the greatest difference of height between two points
     */
    virtual double getPenteMax() const =0;

    /**
     * @return the first point of definition of the Terrain, a
     */
    Vector2D getA() const;

    /**
     * @return the second point of definition of the Terrain, b
     */
    Vector2D getB() const;

    /**
     * Ray Marching. Uses a Ray to calculate its intersection with the Terrain and find the corresponding point. Each step, checks a little further if still in the bounding box of the Terrain, at a steady pace.
     * @param[in] r The Ray to check the collision with
     * @param[in] aBox the first point defining the bounding box
     * @param[in] bBox the second point defining the bounding box
     * @param[out] resu the intersection of the Ray and the surface of the Terrain
     * @param[out] isBox if the intersection of the ray and the Terrain is situated on the bounding box. Used to check if under the Terrain on the first iteration.
     * @see isIn()
     * @return
     */
    bool intersectRayMarching(const Ray &r, const Vector3D &aBox, const Vector3D &bBox, Vector3D &resu, bool &isBox);

    /**
     * TODO
     * @param[in] r The Ray to check the collision with
     * @param[in] aBox the first point defining the bounding box
     * @param[in] bBox the second point defining the bounding box
     * @param[in] pMax the max slope
     * @param[out] resu the intersection of the Ray and the surface of the Terrain
     * @param[out] isBox if the intersection of the ray and the Terrain is situated on the bounding box. Used to check if under the Terrain on the first iteration.
     * @return
     */
    bool intersectAdvanced(const Ray &ray, const Vector3D &aBox, const Vector3D &bBox, double pMax, Vector3D &resu, bool &isBox) const;

    bool intersectAdvancedMax(const Ray &ray, const Vector3D &aBox, const Vector3D &bBox,double pMax, Vector3D &resu, bool& isBox, float distMax) const;

};

    inline Vector2D Terrain::getA() const{
        return a;
    }

    inline Vector2D Terrain::getB() const{
        return b;
    }



#endif // TERRAIN_H
