
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
//    spheres = new Mesh_Sphere*[list->count()];
//    for (int i = 0; i < list->count(); ++i)
//    {
//        spheres[i] = (Mesh_Sphere*)list->item(i);
//    }
    genMesh_MarchingCubes(this);
//    delete spheres;
}

bool Mesh_Blob::MarchingCubesPredicate(QVector3D position)
{
    return true;
}

BoundingBox Mesh_Blob::getMarchingCubesBounds()
{
    BoundingBox result;
//    for (int i = 0; i < list->count(); ++i)
//    {
//        Mesh_Sphere* sphere = spheres[i];

//    }
    return result;
}
