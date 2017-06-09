
#include "mesh.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QDebug>

using namespace std;

QOpenGLFunctions* Mesh::gl = NULL;

Mesh::Mesh() :
    _scale(1), vbo(NULL), vao(NULL)
{
    if (gl == NULL)
    {
        gl = new QOpenGLFunctions();
        gl->initializeOpenGLFunctions();
    }
}

Mesh::~Mesh() {}

void Mesh::draw(QOpenGLShaderProgram* shader)
{
    if (vao != NULL) {
        shader->setUniformValue("modelTransform", modelTransform);
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        vao->release();
    }
}

float Mesh::scale() const
{
    return _scale;
}

void Mesh::setScale(float value)
{
    _scale = value;
    modelTransform.setToIdentity();
    modelTransform.translate(_position);
    modelTransform.scale(_scale, _scale, _scale);
}

QVector3D Mesh::position() const
{
    return _position;
}

void Mesh::setPosition(QVector3D value)
{
    _position = value;
    modelTransform.setToIdentity();
    modelTransform.translate(_position);
    modelTransform.scale(_scale, _scale, _scale);
}


void Mesh::genMesh(const vector<vector<QVector3D>>& meshData)
{
    vector<QVector3D> positions = meshData[0];
    vector<QVector3D> tris = meshData[1];

    vertexCount = (int)tris.size() * 3;
    float* finalVboData = new float[vertexCount * 6];
    int currentResult = 0;
    for (vector<QVector3D>::iterator i = tris.begin(); i != tris.end(); ++i) {
        QVector3D preNormal1 = (positions[(*i)[1]] - positions[(*i)[0]]).normalized();
        QVector3D preNormal2 = (positions[(*i)[2]] - positions[(*i)[0]]).normalized();
        QVector3D normal = QVector3D::crossProduct(preNormal1, preNormal2).normalized();
        for (int j = 0; j < 3; ++j) {
            int currentVector = (*i)[j];
            for (int k = 0; k < 3; ++k) {
                finalVboData[currentResult] = positions[currentVector][k];
                ++currentResult;
            }
            for (int k = 0; k < 3; ++k) {
                finalVboData[currentResult] = normal[k];
                ++currentResult;
            }
        }
    }

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(finalVboData, vertexCount * 6 * 4);
    gl->glEnableVertexAttribArray(1);
    gl->glEnableVertexAttribArray(2);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, false, 6*4, 0);
    gl->glVertexAttribPointer(2, 3, GL_FLOAT, false, 6*4, (void*)(3*4));
    vbo->release();
    vao->release();
}
