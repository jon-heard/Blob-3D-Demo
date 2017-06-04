
#include "BlobScene.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include "Sphere.h"
#include <QDebug>

using namespace std;

BlobScene::BlobScene(QWidget *parent)
    : QOpenGLWidget(parent) {}

BlobScene::~BlobScene()
{
    for (int i = 0; i < spheres.size(); ++i) {
        delete spheres[i];
    }
    delete shader_basic;
}

void BlobScene::initializeGL()
{
    glClearColor(.25,.25,.25,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    shader_basic = new QOpenGLShaderProgram();
    shader_basic->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_basic.vert");
    shader_basic->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag_basic.frag");
    shader_basic->link();

    Sphere* sphere;

    sphere = new Sphere(shader_basic);
    spheres.push_back(sphere);
    sphere->setScale(.5);
    sphere->setPosition(QVector3D(0,1,0));

    sphere = new Sphere(shader_basic);
    spheres.push_back(sphere);
    sphere->setScale(1);
    sphere->setPosition(QVector3D(0,-1,0));

    sphere = new Sphere(shader_basic);
    spheres.push_back(sphere);
    sphere->setScale(1);
    sphere->setPosition(QVector3D(1,0,0));

    sphere = new Sphere(shader_basic);
    spheres.push_back(sphere);
    sphere->setScale(1);
    sphere->setPosition(QVector3D(-1,0,0));

    sceneTransform.setToIdentity();
    sceneTransform.translate(0, 0, -5);
}

void BlobScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_basic->bind();
    shader_basic->setUniformValue("projectionTransform", projectionTransform);
    shader_basic->setUniformValue("sceneTransform", sceneTransform);
    for (int i = 0; i < spheres.size(); ++i)
    {
        spheres[i]->draw();
    }
    shader_basic->release();
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
