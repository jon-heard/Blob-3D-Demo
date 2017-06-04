#ifndef MESH_MARCHINGCUBES_H
#define MESH_MARCHINGCUBES_H

#include "Mesh.h"

class QOpenGLShaderProgram;

class Mesh_MarchingCubes : public Mesh
{
public:
    Mesh_MarchingCubes(QOpenGLShaderProgram* shader);
};

#endif // MESH_MARCHINGCUBES_H
