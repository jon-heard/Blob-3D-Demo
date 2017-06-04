#ifndef BLOBSCENE_H
#define BLOBSCENE_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <vector>

class QOpenGLShaderProgram;
class Sphere;
class QListWidget;

class BlobScene : public QOpenGLWidget
{
public:
    BlobScene(QWidget *parent = 0);
    ~BlobScene();
    QListWidget* list();
    void setList(QListWidget* value);
    Sphere* makeSphere();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QMatrix4x4 projectionTransform;

    QMatrix4x4 sceneTransform;
    QPoint rotation;
    QPoint previousRotation;
    QPoint previousPos;

    int vertexCount;
    QOpenGLShaderProgram* shader_basic;

    QListWidget* _list;
    Sphere* sphere;
};

#endif // BLOBSCENE_H
