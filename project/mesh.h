#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QVector3D>
#include <QMatrix4x4>

class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

class Mesh
{
public:
    Mesh(QOpenGLShaderProgram* shader);
    virtual ~Mesh();
    void draw();

    void setScale(float value);
    float scale();
    void setPosition(QVector3D value);
    QVector3D position();
protected:
    void genMesh(std::vector<QVector3D>** meshData);

    QOpenGLShaderProgram* shader;
    QOpenGLBuffer* vbo;
    QOpenGLVertexArrayObject* vao;

    int vertexCount;

    QMatrix4x4 modelTransform;
    float _scale;
    QVector3D _position;
};

#endif // MESH_H
