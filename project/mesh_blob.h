#ifndef MESH_BLOB_H
#define MESH_BLOB_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;

class Mesh_Blob : public Mesh_MarchingCubes
{
public:
    Mesh_Blob(QOpenGLShaderProgram* shader);
};

#endif // MESH_BLOB_H
