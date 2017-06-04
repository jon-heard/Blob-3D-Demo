#ifndef MESH_BLOB_H
#define MESH_BLOB_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;

class Mesh_Blob : public Mesh_MarchingCubes, public Mesh_MarchingCubesData
{
public:
    Mesh_Blob(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Blob();
    void genMesh_Blob();
    bool MarchingCubesPredicate(QVector3D position);
    BoundingBox getMarchingCubesBounds();
protected:
    QListWidget* list;
    Mesh_Sphere** spheres;
};

#endif // MESH_BLOB_H
