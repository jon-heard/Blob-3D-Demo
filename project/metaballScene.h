#ifndef METABALLSCENE_H
#define METABALLSCENE_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <vector>

class QOpenGLShaderProgram;
class QListWidget;
class Mesh_Sphere;
class Mesh_Metaballs;

class MetaballScene : public QOpenGLWidget
{
public:
    MetaballScene(QWidget *parent = 0);
    ~MetaballScene();
    QListWidget* list() const;
    void setList(QListWidget* value);
    Mesh_Sphere* makeSphere() const;
    void updateMetaballMesh();
    bool isRenderingMetaballs() const;
    void setIsRenderingMetaballs(bool value);
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
    Mesh_Metaballs* metaballs;

    // Shaders
    QOpenGLShaderProgram* shader_basic;

    // UI
    QListWidget* _list;
    bool _isRenderingMetaballs;
};

#endif // METABALLSCENE_H
