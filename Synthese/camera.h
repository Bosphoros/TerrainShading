#ifndef CAMERA_H
#define CAMERA_H
#include "vector3d.h"
#include <QImage>
#include <QRgb>
#include "terrain.h"

/**
 * @brief The Camera class
 */
class Camera
{
private:
    Vector3D origine; /**< The origin of the camera */
    Vector3D w; /**< The direction the camera is pointing at */
    Vector3D u;/**< The direction along the width of the screen*/
    Vector3D v;/**< The direction along the height of the screen*/
    double dw;/**< The distance between the origin of the camera and the center of the screen*/
    double lw;/**< The distance between the center of the screen and its borders along u*/
    double lh;/**< The distance between the center of the screen and its borders alogn v*/
public:
    /**
    * Constructor of a Camera
    * @param[in] o the origin point of the camera
    * @param[in] at the point the Camera is focused on
    * @param[in] d the distance separating the origin of the Camera and the center of the screen
    */
    Camera(const Vector3D& o, const Vector3D& at,double d);

    /**
     * Finds the color of a pixel on the screen according to the Camera seetings and a Terrain
     * @param[in] t the Terrain the Camera has to launch ray towards
     * @param[in] aBox the coordinates of the first point describing the bounding box of the Terrain
     * @param[in] bBox the coordinates of the second point describing the bounding box of the Terrain
     * @param[in] s the position of the sun
     * @param[in] i the number of the column of the pixel
     * @param[in] j the number of the row of the pixel
     * @param[in] l the the width of the screen
     * @param[in] h the height of the screen
     * @param[in] pMax the max slope
     * @see printScreen()
     * @return the QRgb value of the pixel
     */
    QRgb ptScreen(Terrain* const t, const Vector3D &aBox, const Vector3D &bBox, const Vector3D &s, int i, int j, int l, int h, double pMax) const;
    /**
     * Crates a QImage representing the Camera's point of view of a Terrain
     * @param[in] t the Terrain the Camera has to launch ray towards
     * @param[in] s the position of the sun
     * @param[in] l the the width of the screen
     * @param[in] h the height of the screen
     * @return the QImage containing the screen shot
     */
    QImage printScreen(Terrain * const t, const Vector3D& s, int l, int h) const;

    /**
     * Translate the position of the Camera according to a direction vector
     * @param[in] v the movement the Camera has to be moved by
     */
    void translate(const Vector3D& v);

};

#endif // CAMERA_H
