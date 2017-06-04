#ifndef BLOBSCENE_H
#define BLOBSCENE_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <vector>

class QOpenGLShaderProgram;
class Sphere;

class BlobScene : public QOpenGLWidget
{
public:
    BlobScene(QWidget *parent = 0);
    ~BlobScene();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QMatrix4x4 projectionTransform;
    QPoint rotation;
    QPoint previousRotation;
    QPoint previousPos;
    QMatrix4x4 sceneTransform;
    int vertexCount;
    QOpenGLShaderProgram* shader_basic;
    std::vector<Sphere*> spheres;
};

#endif // BLOBSCENE_H
