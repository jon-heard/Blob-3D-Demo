
#include "BlobScene.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include "mesh_sphere.h"
#include "mesh_blob.h"
#include <QDebug>
#include <QListWidget>

using namespace std;

BlobScene::BlobScene(QWidget *parent)
    : QOpenGLWidget(parent), sphere(NULL), _blobify(false) {}

BlobScene::~BlobScene()
{
    delete sphere;
    delete shader_basic;
}

QListWidget* BlobScene::list()
{
    return _list;
}

void BlobScene::setList(QListWidget* value)
{
    _list = value;
}


Mesh_Sphere* BlobScene::makeSphere()
{
    shader_basic->bind();
    return new Mesh_Sphere(shader_basic);
    shader_basic->release();
}

void BlobScene::updateBlob()
{
    blob->genMesh_Blob();
}

bool BlobScene::blobify()
{
    return _blobify;
}

void BlobScene::setBlobify(bool value)
{
    _blobify = value;
    repaint();
}

void BlobScene::initializeGL()
{
    glClearColor(.25,.25,.25,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    sceneTransform.setToIdentity();
    sceneTransform.translate(0, 0, -5);

    shader_basic = new QOpenGLShaderProgram();
    shader_basic->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_basic.vert");
    shader_basic->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag_basic.frag");
    shader_basic->link();

    shader_basic->bind();
    sphere = new Mesh_Sphere(shader_basic);
    blob = new Mesh_Blob(shader_basic);
    shader_basic->release();
}

void BlobScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_list != NULL)
    {
        shader_basic->bind();
        shader_basic->setUniformValue("projectionTransform", projectionTransform);
        shader_basic->setUniformValue("sceneTransform", sceneTransform);
        if (_blobify)
        {
            blob->draw();
        } else {
            for (int i = 0; i < _list->count(); ++i)
            {
                ((Mesh_Sphere*)_list->item(i))->draw();
            }
        }
        shader_basic->release();
    }
}

void BlobScene::resizeGL(int w, int h)
{
    projectionTransform.setToIdentity();
    projectionTransform.perspective(45, (float)w/h, 0.01f, 100.0f);
}

void BlobScene::mousePressEvent(QMouseEvent *event)
{
    previousPos = event->pos();
    previousRotation = rotation;
}

void BlobScene::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        rotation.setY(previousRotation.y() + (event->x() - previousPos.x()));
        rotation.setX(previousRotation.x() + (event->y() - previousPos.y()));
        sceneTransform.setToIdentity();
        sceneTransform.translate(0, 0, -5);
        sceneTransform.rotate(rotation.x(), 1, 0, 0);
        sceneTransform.rotate(rotation.y(), 0, 1, 0);
        repaint();
    }
}
