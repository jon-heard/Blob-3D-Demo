#ifndef MESH_BLOB_H
#define MESH_BLOB_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;

class Mesh_Blob : public Mesh_MarchingCubes, public Mesh_MarchingCubesParameters
{
public:
    Mesh_Blob(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Blob();
    QListWidget* list();
    void setList(QListWidget* value);
    void genMesh_Blob();
    bool MarchingCubes_getIsWithin(QVector3D position);
    BoundingBox MarchingCubes_getBounds();
protected:
    QListWidget* _list;

    int sphereCount;
    Mesh_Sphere** spheres;
};

#endif // MESH_BLOB_H
