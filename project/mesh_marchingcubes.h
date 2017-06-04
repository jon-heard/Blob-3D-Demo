#ifndef MESH_MARCHINGCUBES_H
#define MESH_MARCHINGCUBES_H

#include "Mesh.h"
#include <QVector3D>

const int MARCHING_CUBE_SIZE = 1;

class QOpenGLShaderProgram;

class Mesh_MarchingCubesData
{
    virtual bool MarchingCubesPredicate(QVector3D position) = 0;
};

class Mesh_MarchingCubes : public Mesh
{
public:
    Mesh_MarchingCubes(QOpenGLShaderProgram* shader);
    virtual ~Mesh_MarchingCubes();

    void genMesh_MarchingCubes(Mesh_MarchingCubesData* predicate);
};

#endif // MESH_MARCHINGCUBES_H
