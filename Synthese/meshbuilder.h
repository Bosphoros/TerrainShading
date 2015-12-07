#ifndef MESHBUILDER_H
#define MESHBUILDER_H
#include "mesh.h"
#include <QString>
#include "terrain.h"
#include "vector2d.h"

/**
 * @brief The MeshBuilder class, contains methods to create and load meshes
 */
class MeshBuilder
{
public:
    /**
     * Empty MeshBuilder constructor
     */
    MeshBuilder();

    /**
     * Loads a mesh for a file
     * @param nom The file location to load from
     * @return The constructed mesh
     */
    Mesh loadMesh(const QString& nom) const;

    /**
     * Saves the mesh to a file
     * @param nom The file location to save in
     * @param mesh The mesh to save
     */
    void saveMesh(const QString& nom, const Mesh &mesh) const;

    /**
     * Destructor of MeshBuilder, empty.
     */
    ~MeshBuilder();

    /**
     * Creates a Mesh based on a Terrain
     * @param t The Terrain to base the Mesh on
     * @param e The number of samples
     * @param nom The name of the mesh to create
     * @return A Mesh based on samples of t
     */
    Mesh terrain(const Terrain &t, int e, const QString &nom) const;


};
#endif // MESHBUILDER_H
