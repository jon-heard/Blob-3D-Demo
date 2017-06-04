#ifndef MESH_BLOB_H
#define MESH_BLOB_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;
class QListWidget;

class Mesh_Blob : public Mesh_MarchingCubes, public Mesh_MarchingCubesData
{
public:
    Mesh_Blob(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Blob();
    void genMesh_Blob();
    bool MarchingCubesPredicate(QVector3D position);
protected:
    QListWidget* list;
};

#endif // MESH_BLOB_H
