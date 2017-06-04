#ifndef MESH_SPHERE_H
#define MESH_SPHERE_H

#include "mesh.h"
#include <QListWidgetItem>
#include <QString>

const int SPHERE_DIVISION = 3;

class Mesh_Sphere : public Mesh, public QListWidgetItem
{
public:
    Mesh_Sphere(QOpenGLShaderProgram* shader);
    virtual ~Mesh_Sphere();
    virtual void setScale(float value);
    virtual void setPosition(QVector3D value);
    void refreshTextDisplay();
protected:
    void genSphereMesh();
    static int instanceCount;
private:
    static QOpenGLBuffer* sphereVbo;
    static QOpenGLVertexArrayObject* sphereVao;
    static int sphereVertexCount;
};

#endif // MESH_SPHERE_H
