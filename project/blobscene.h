#ifndef BLOBSCENE_H
#define BLOBSCENE_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <vector>

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;
class Mesh_Blob;

class BlobScene : public QOpenGLWidget
{
public:
    BlobScene(QWidget *parent = 0);
    ~BlobScene();
    QListWidget* list();
    void setList(QListWidget* value);
    Mesh_Sphere* makeSphere();
    void updateBlob();
    bool blobify();
    void setBlobify(bool value);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void refreshSceneTransform();
private:
    // Projection transform
    QMatrix4x4 projectionTransform;

    // Scene transform
    QMatrix4x4 sceneTransform;
    float zoom;
    QPoint rotation;
    QPoint previousRotation;
    QPoint previousPos;

    // Meshes
    Mesh_Blob* blob;
    Mesh_Sphere* sphere;

    // Shaders
    QOpenGLShaderProgram* shader_basic;

    // UI
    QListWidget* _list;
    bool _blobify;
};

#endif // BLOBSCENE_H
