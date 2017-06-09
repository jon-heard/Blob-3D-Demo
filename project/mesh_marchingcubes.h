#ifndef MESH_MARCHINGCUBES_H
#define MESH_MARCHINGCUBES_H

#include "Mesh.h"
#include <QVector3D>
#include <vector>

const float MARCHING_CUBE_SIZE = .05f;

class QOpenGLShaderProgram;

class BoundingBox
{
public:
    QVector3D low;
    QVector3D high;
};

class Mesh_MarchingCubesParameters
{
public:
    virtual bool Mesh_MarchingCubeParameters_getIsWithin(QVector3D position) = 0;
    virtual BoundingBox Mesh_MarchingCubeParameters_getBounds() = 0;
};

class Mesh_MarchingCubes : public Mesh
{
public:
    virtual ~Mesh_MarchingCubes();
    bool dirty() const;
    void setDirty(bool value);

    void genMesh_BoundingBox(Mesh_MarchingCubesParameters* parameters);
    void genMesh_MarchingCubes(Mesh_MarchingCubesParameters* parameters);
private:
    void addVectorsToMesh(QVector3D offset, std::vector<QVector3D> vertices, std::vector<QVector3D>& positions, std::vector<QVector3D>& tris);
    bool _dirty;
};

#endif // MESH_MARCHINGCUBES_H
