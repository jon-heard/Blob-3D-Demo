#ifndef MESH_MARCHINGCUBES_H
#define MESH_MARCHINGCUBES_H

#include "Mesh.h"
#include <QVector3D>

const float MARCHING_CUBE_SIZE = .125;

class QOpenGLShaderProgram;

class BoundingBox
{
public:
    QVector3D corner1;
    QVector3D corner2;
};

class Mesh_MarchingCubesData
{
    virtual bool MarchingCubesPredicate(QVector3D position) = 0;
    virtual BoundingBox getMarchingCubesBounds() = 0;
};

class Mesh_MarchingCubes : public Mesh
{
public:
    Mesh_MarchingCubes(QOpenGLShaderProgram* shader);
    virtual ~Mesh_MarchingCubes();

    void genMesh_MarchingCubes(Mesh_MarchingCubesData* predicate);
};

#endif // MESH_MARCHINGCUBES_H
