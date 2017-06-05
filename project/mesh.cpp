
#include "mesh.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDebug>

using namespace std;

Mesh::Mesh(QOpenGLShaderProgram* shader) :
    _scale(1), vbo(NULL), vao(NULL)
{
    this->shader = shader;
}

Mesh::~Mesh() {}

void Mesh::draw()
{
    if (vao != NULL) {
        shader->setUniformValue("modelTransform", modelTransform);
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        vao->release();
    }
}

void Mesh::setScale(float value)
{
    _scale = value;
    modelTransform.setToIdentity();
    modelTransform.translate(_position);
    modelTransform.scale(_scale, _scale, _scale);
}

float Mesh::scale()
{
    return _scale;
}

void Mesh::setPosition(QVector3D value)
{
    _position = value;
    modelTransform.setToIdentity();
    modelTransform.translate(_position);
    modelTransform.scale(_scale, _scale, _scale);
}

QVector3D Mesh::position()
{
    return _position;
}


void Mesh::genMesh(vector<QVector3D>** meshData)
{
    vector<QVector3D>* positions = meshData[0];
    vector<QVector3D>* tris = meshData[1];

    vertexCount = (int)tris->size() * 3;
    float* result = new float[vertexCount * 7];
    int currentResult = 0;
    for (vector<QVector3D>::iterator i = tris->begin();
         i != tris->end(); ++i) {
        QVector3D preNormal1 = ((*positions)[(*i)[1]] - (*positions)[(*i)[0]]).normalized();
        QVector3D preNormal2 = ((*positions)[(*i)[2]] - (*positions)[(*i)[0]]).normalized();
        QVector3D normal = QVector3D::crossProduct(preNormal1, preNormal2).normalized();
        for (int j = 0; j < 3; ++j) {
            int currentVector = (*i)[j];
            for (int k = 0; k < 3; ++k) {
                result[currentResult] = (*positions)[currentVector][k];
                ++currentResult;
            }
            for (int k = 0; k < 3; ++k) {
                result[currentResult] = normal[k];
                ++currentResult;
            }
        }
    }

    shader->bind();

    vbo = new QOpenGLBuffer();
    //vbo->create();
    if(!vbo->create())
    {
        qInfo() << "VBO: here it is";
    }
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(result, vertexCount * 6 * 4);

    vao = new QOpenGLVertexArrayObject();
    if(!vao->create())
    {
        qInfo() << "VAO: here it is";
    }
    vao->bind();
    shader->enableAttributeArray("position");
    shader->enableAttributeArray("normal");
    shader->setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * 4);
    shader->setAttributeBuffer("normal", GL_FLOAT, 3 * 4, 3, 6 * 4);

    vao->release();
    vbo->release();
    shader->release();
}
