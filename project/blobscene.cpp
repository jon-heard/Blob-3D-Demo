
#include "BlobScene.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include "Sphere.h"
#include <QDebug>
#include <QListWidget>

using namespace std;

BlobScene::BlobScene(QWidget *parent)
    : QOpenGLWidget(parent), sphere(NULL) {}

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


Sphere* BlobScene::makeSphere()
{
    shader_basic->bind();
    return new Sphere(shader_basic);
    shader_basic->release();
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
    sphere = new Sphere(shader_basic);
    //delete sphere;
    //sphere = NULL;
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
        for (int i = 0; i < _list->count(); ++i)
        {
            ((Sphere*)_list->item(i))->draw();
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
