#ifndef MESH_H
#define MESH_H
#include "vector3d.h"
#include <QMatrix3x3>
#include<QList>

/**
 * @brief The Mesh class
 */
class Mesh
{
private:
    QString nom; /**< The name of the object*/
    QList<Vector3D> geom; /**< List of vertices composing the mesh*/
    QList<int> topo; /**< Topology of the mesh */
    QList<Vector3D> norm; /**< Normals of the geoms */
public:
    /**
     * @brief Empty Mesh constructor. The lists are not initialized with anything.
     */
    Mesh();

    /**
     * Copy Mesh constructor. Basic one, not directly implemented.
     * @param m the mesh to copy
     */
    Mesh(const Mesh& m);

    /**
     * Mesh constructor.
     * @param v The list of vertices
     * @param t The list containing the topology of the mesh
     * @param n The list of normals of the vertices
     * @param no The name of the mesh
     */
    Mesh(const QList<Vector3D>& v, const QList<int>& t, const QList<Vector3D>& n,const QString& no);

    /**
     * Translates every vertice by a Vector3D
     * @param t The vector to translate by
     */
    void translate(const Vector3D& t);

    /**
     * Rotates every vertice with a rotation matrix
     * @param mat The rotation matrix
     */
    void rotate(const QMatrix3x3& mat);

    /**
     * Applies an homotecy
     * @param c The central point of the homotecy
     * @param h The factor of the homotecy
     */
    void homotecie(const Vector3D &c, double h);

    /**
     * Merges two meshes in the same object
     * @param mesh The other mesh to merge
     */
    void merge(const Mesh& mesh);

    /**
     * Finds the index of a vertice in geom
     * @param g The vertice to find
     * @return The index of the vertice. -1 if not found
     */
    int containsGeom(const Vector3D& g);

    /**
     * Finds the index of a normal if norm
     * @param n The normal to find
     * @return The index of the vertice. -1 if not found
     */
    int containsNorm(const Vector3D& n);

    /**
     * Getter of geom
     * @return A const reference of geom
     */
    const QList<Vector3D> &getGeom() const;

    /**
     * Getter of norm
     * @return A const reference of norm
     */
    const QList<Vector3D> &getNorm() const;

    /**
     * Getter of topo
     * @return A const reference of topo
     */
    const QList<int> &getTopo() const;

    /**
     * Getter of nom
     * @return A const reference of nom
     */
    const QString& getNom() const;
    ~Mesh();
};

#endif // MESH_H
