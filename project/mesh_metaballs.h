#ifndef MESH_METABALL_H
#define MESH_METABALL_H

#include "mesh_marchingcubes.h"

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;

class Mesh_Metaballs : public Mesh_MarchingCubes, public Mesh_MarchingCubesParameters
{
public:
    Mesh_Metaballs(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Metaballs();
    QListWidget* list() const;
    void setList(QListWidget* value);
    void genMesh_Metaball();
    bool Mesh_MarchingCubeParameters_getIsWithin(QVector3D position);
    BoundingBox Mesh_MarchingCubeParameters_getBounds();
protected:
    QListWidget* _listOfSpheres;
};

#endif // MESH_METABALL_H
