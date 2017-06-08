#ifndef MESH_MARCHINGCUBES_H
#define MESH_MARCHINGCUBES_H

#include "Mesh.h"
#include <QVector3D>
#include <vector>

const float MARCHING_CUBE_SIZE = .025f;

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
    virtual bool MarchingCubes_getIsWithin(QVector3D position) = 0;
    virtual BoundingBox MarchingCubes_getBounds() = 0;
};

class Mesh_MarchingCubes : public Mesh
{
public:
    Mesh_MarchingCubes(QOpenGLShaderProgram* shader);
    virtual ~Mesh_MarchingCubes();
    bool dirty();
    void setDirty(bool value);

    void genMesh_MarchingCubes(Mesh_MarchingCubesParameters* parameters);
private:
    void addVectorsToMesh(QVector3D offset, std::vector<QVector3D> vertices, std::vector<QVector3D>& positions, std::vector<QVector3D>& tris);
    void addCubeToMesh(std::vector<QVector3D> hits, QVector3D position, std::vector<QVector3D>& positions, std::vector<QVector3D>& tris);
    bool _dirty;
};

#endif // MESH_MARCHINGCUBES_H
