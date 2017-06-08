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

    float scale() const;
    virtual void setScale(float value);
    QVector3D position() const;
    virtual void setPosition(QVector3D value);
protected:
    void genMesh(const std::vector<std::vector<QVector3D>>& meshData);

    QOpenGLShaderProgram* shader;
    QOpenGLBuffer* vbo;
    QOpenGLVertexArrayObject* vao;

    int vertexCount;

    QMatrix4x4 modelTransform;
    float _scale;
    QVector3D _position;
};

#endif // MESH_H
