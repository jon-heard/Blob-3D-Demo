#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

const int SPHERE_DIVISION = 3;

class Sphere : public Mesh
{
public:
    Sphere(QOpenGLShaderProgram* shader);
    virtual ~Sphere();
protected:
    void genSphereMesh();
    static int instanceCount;
private:
    static QOpenGLBuffer* sphereVbo;
    static QOpenGLVertexArrayObject* sphereVao;
    static int sphereVertexCount;
};

#endif // SPHERE_H
