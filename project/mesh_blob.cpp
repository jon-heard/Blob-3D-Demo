
#include "mesh_blob.h"
#include <QOpenGLShaderProgram>
#include <QListWidget>
#include <QDebug>

Mesh_Blob::Mesh_Blob(QOpenGLShaderProgram* shader) : Mesh_MarchingCubes(shader)
{
    genMesh_Blob();
}

Mesh_Blob::~Mesh_Blob() {}

void Mesh_Blob::genMesh_Blob()
{
    genMesh_MarchingCubes(this);
}

bool Mesh_Blob::MarchingCubesPredicate(QVector3D position)
{
    return true;
}
