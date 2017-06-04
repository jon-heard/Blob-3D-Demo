
#include "mesh_blob.h"
#include <QOpenGLShaderProgram>
#include <QListWidget>
#include <QDebug>

Mesh_Blob::Mesh_Blob(QOpenGLShaderProgram* shader) :
    Mesh_MarchingCubes(shader), _list(NULL)
{
    //genMesh_Blob();
    genMesh_MarchingCubes(this);
}

Mesh_Blob::~Mesh_Blob() {}

QListWidget* Mesh_Blob::list()
{
    return _list;
}

void Mesh_Blob::setList(QListWidget* value)
{
    _list = value;
}


void Mesh_Blob::genMesh_Blob()
{
    if (_list != NULL && _list->count() > 0) {
        sphereCount = _list->count();
        spheres = new Mesh_Sphere*[sphereCount];
        for (int i = 0; i < _list->count(); ++i)
        {
            spheres[i] = (Mesh_Sphere*)_list->item(i);
        }
        genMesh_MarchingCubes(this);
        delete spheres;
    } else {
        genMesh_MarchingCubes(NULL);
    }
}

bool Mesh_Blob::MarchingCubesPredicate(QVector3D position)
{
    return true;
}

BoundingBox Mesh_Blob::getMarchingCubesBounds()
{
    BoundingBox result;
    if (sphereCount > 0)
    {
        for (int i = 0; i < _list->count(); ++i)
        {
            Mesh_Sphere* sphere = spheres[i];
        }
    }
    return result;
}
