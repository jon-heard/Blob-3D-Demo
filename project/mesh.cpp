
#include "mesh.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDebug>

using namespace std;

Mesh::Mesh(QOpenGLShaderProgram* shader) : _scale(1)
{
    this->shader = shader;
}

Mesh::~Mesh() {}

void Mesh::draw()
{
    shader->setUniformValue("modelTransform", modelTransform);
    vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    vao->release();
}

void Mesh::setScale(float value)
{
    _scale = value;
    modelTransform.setToIdentity();
    modelTransform.scale(_scale, _scale, _scale);
    modelTransform.translate(_position);
}

float Mesh::scale()
{
    return _scale;
}

void Mesh::setPosition(QVector3D value)
{
    _position = value;
    modelTransform.setToIdentity();
    modelTransform.scale(_scale, _scale, _scale);
    modelTransform.translate(_position);
}

QVector3D Mesh::position()
{
    return _position;
}


void Mesh::genMesh(vector<QVector3D>** meshData)
{
    vector<QVector3D>* positions = meshData[0];
    vector<QVector3D>* tris = meshData[1];
    vector<QVector3D>* voltage = meshData[2];

    vertexCount = (int)tris->size() * 3;
    float* result = new float[vertexCount * 7];
    int currentResult = 0;
    for (int i = 0; i < tris->size(); ++i) {
        QVector3D preNormal1 = ((*positions)[(*tris)[i][1]] - (*positions)[(*tris)[i][0]]).normalized();
        QVector3D preNormal2 = ((*positions)[(*tris)[i][2]] - (*positions)[(*tris)[i][0]]).normalized();
        QVector3D normal = QVector3D::crossProduct(preNormal1, preNormal2).normalized();
        for (int j = 0; j < 3; ++j) {
            int currentVector = (*tris)[i][j];
            for (int k = 0; k < 3; ++k) {
                result[currentResult] = (*positions)[currentVector][k];
                ++currentResult;
            }
            for (int k = 0; k < 3; ++k) {
                result[currentResult] = normal[k];
                ++currentResult;
            }
            result[currentResult] = (*voltage)[currentVector][0];
            ++currentResult;
        }
    }

    shader->bind();

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(result, vertexCount * 7 * 4);

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    shader->enableAttributeArray("position");
    shader->enableAttributeArray("normal");
    shader->enableAttributeArray("voltage");
    shader->setAttributeBuffer("position", GL_FLOAT, 0, 3, 7 * 4);
    shader->setAttributeBuffer("normal", GL_FLOAT, 3 * 4, 3, 7 * 4);
    shader->setAttributeBuffer("voltage", GL_FLOAT, 6 * 4, 1, 7 * 4);

    vao->release();
    vbo->release();
    shader->release();
}
