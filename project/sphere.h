#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"
#include <QListWidgetItem>
#include <QString>

const int SPHERE_DIVISION = 3;

class Sphere : public Mesh, public QListWidgetItem
{
public:
    Sphere(QOpenGLShaderProgram* shader);
    virtual ~Sphere();
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

#endif // SPHERE_H
