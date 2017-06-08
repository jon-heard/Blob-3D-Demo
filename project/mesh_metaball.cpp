
#include "mesh_metaball.h"
#include <QOpenGLShaderProgram>
#include <QListWidget>
#include <QDebug>
#include <mesh_sphere.h>

Mesh_Metaball::Mesh_Metaball(QOpenGLShaderProgram* shader) :
    Mesh_MarchingCubes(shader), _listOfSpheres(NULL)
{
    genMesh_Metaball();
}

Mesh_Metaball::~Mesh_Metaball() {}

QListWidget* Mesh_Metaball::list() const
{
    return _listOfSpheres;
}

void Mesh_Metaball::setList(QListWidget* value)
{
    _listOfSpheres = value;
}


void Mesh_Metaball::genMesh_Metaball()
{
    if (_listOfSpheres != NULL && _listOfSpheres->count() > 0) {
        genMesh_MarchingCubes(this);
    } else {
        genMesh_MarchingCubes(NULL);
    }
}

bool Mesh_Metaball::Mesh_MarchingCubeParameters_getIsWithin(QVector3D position)
{
    float intensity = 0;
    int sphereCount = _listOfSpheres->count();
    for (int i = 0; i < sphereCount; ++i) {
        Mesh_Sphere* sphere = (Mesh_Sphere*)_listOfSpheres->item(i);
        intensity += sphere->scale() / (sphere->position()-position).length();
    }
    return intensity > 1.5;
}

BoundingBox Mesh_Metaball::Mesh_MarchingCubeParameters_getBounds()
{
    BoundingBox result;
    if (_listOfSpheres != NULL && _listOfSpheres->count() > 0)
    {
        int sphereCount = _listOfSpheres->count();
        for (int i = 0; i < sphereCount; ++i)
        {
            Mesh_Sphere* sphere = (Mesh_Sphere*)_listOfSpheres->item(i);
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
