#ifndef MESH_BLOB_H
#define MESH_BLOB_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;

class Mesh_Metaball : public Mesh_MarchingCubes, public Mesh_MarchingCubesParameters
{
public:
    Mesh_Metaball(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Metaball();
    QListWidget* list() const;
    void setList(QListWidget* value);
    void genMesh_Blob();
    bool MarchingCubes_getIsWithin(QVector3D position);
    BoundingBox MarchingCubes_getBounds();
protected:
    QListWidget* _listOfSpheres;
};

#endif // MESH_BLOB_H
