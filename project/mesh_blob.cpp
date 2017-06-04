
#include "mesh_blob.h"
#include <QOpenGLShaderProgram>
#include <QListWidget>
#include <QDebug>
#include <mesh_sphere.h>

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

bool Mesh_Blob::MarchingCubes_getIsWithin(QVector3D position)
{
    for (int i = 0; i < sphereCount; ++i) {
        QVector3D spherePosition = spheres[i]->position();
        if ((spherePosition-position).length() < spheres[i]->scale())
        {
            return true;
        }
    }
    return false;
}

BoundingBox Mesh_Blob::MarchingCubes_getBounds()
{
    BoundingBox result;
    if (sphereCount > 0)
    {
        for (int i = 0; i < _list->count(); ++i)
        {
            Mesh_Sphere* sphere = spheres[i];
            float scale = sphere->scale();
            if (sphere->position().x() - scale < result.low.x())
            {
                result.low.setX(sphere->position().x() - scale);
            }
            if (sphere->position().y() - scale < result.low.y())
            {
                result.low.setY(sphere->position().y() - scale);
            }
            if (sphere->position().z() - scale < result.low.z())
            {
                result.low.setZ(sphere->position().z() - scale);
            }

            if (sphere->position().x() + scale > result.high.x())
            {
                result.high.setX(sphere->position().x() + scale);
            }
            if (sphere->position().y() + scale > result.high.y())
            {
                result.high.setY(sphere->position().y() + scale);
            }
            if (sphere->position().z() + scale > result.high.z())
            {
                result.high.setZ(sphere->position().z() + scale);
            }
        }
    }
    return result;
}
