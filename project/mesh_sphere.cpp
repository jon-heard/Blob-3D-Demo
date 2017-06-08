
#include "mesh_sphere.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDebug>

using namespace std;

QOpenGLBuffer* Mesh_Sphere::sphereVbo = NULL;
QOpenGLVertexArrayObject* Mesh_Sphere::sphereVao = NULL;
int Mesh_Sphere::sphereVertexCount = 0;

Mesh_Sphere::Mesh_Sphere(QOpenGLShaderProgram* shader) : Mesh(shader)
{
    if (Mesh_Sphere::sphereVbo == 0)
    {
        genMesh_Sphere();
        Mesh_Sphere::sphereVbo = vbo;
        Mesh_Sphere::sphereVao = vao;
        Mesh_Sphere::sphereVertexCount = vertexCount;
    } else {
        vbo = Mesh_Sphere::sphereVbo;
        vao = Mesh_Sphere::sphereVao;
        vertexCount = Mesh_Sphere::sphereVertexCount;
    }
    refreshTextDisplay();
}

Mesh_Sphere::~Mesh_Sphere() {}

void Mesh_Sphere::setScale(float value)
{
    Mesh::setScale(value);
    refreshTextDisplay();
}

void Mesh_Sphere::setPosition(QVector3D value)
{
    Mesh::setPosition(value);
    refreshTextDisplay();
}

void Mesh_Sphere::refreshTextDisplay()
{
    QString display = QString("[(%1, %2, %3), %4]").arg(_position.x()).arg(_position.y()).arg(_position.z()).arg(_scale);
    setText(display);
}

void Mesh_Sphere::genMesh_Sphere()
{
    // Setup initial icosphere (a cube)
    vector<QVector3D> positions({
                                    {-1, -1, -1},
                                    {1, -1, -1},
                                    {-1, -1, 1},
                                    {1, -1, 1},
                                    {-1, 1, -1},
                                    {1, 1, -1},
                                    {-1, 1, 1},
                                    {1, 1, 1}
                                });
    vector<QVector3D> tris({
                               {0, 1, 2}, {3, 2, 1}, // y-neg
                               {4, 6, 5}, {7, 5, 6}, // y-pos
                               {4, 0, 6}, {2, 6, 0}, // x-neg
                               {5, 7, 1}, {3, 1, 7}, // x-pos
                               {4, 5, 0}, {1, 0, 5}, // z-neg
                               {6, 2, 7}, {3, 7, 2}  // z-pos
                           });

    // subdivide
    for (int i = 0; i < SPHERE_DIVISION; ++i)
    {
        int triCount = (int)tris.size();
        for (int i = 0; i < triCount; ++i) {
            QVector3D oldPosition1 = positions[tris[i][0]];
            QVector3D oldPosition2 = positions[tris[i][1]];
            QVector3D oldPosition3 = positions[tris[i][2]];
            int newPositionIndex = (int)positions.size();
            positions.push_back((oldPosition1 + oldPosition2) / 2);
            positions.push_back((oldPosition2 + oldPosition3) / 2);
            positions.push_back((oldPosition1 + oldPosition3) / 2);
            tris.push_back(QVector3D(newPositionIndex + 2, tris[i][0], newPositionIndex + 0));
            tris.push_back(QVector3D(newPositionIndex + 1, newPositionIndex + 0, tris[i][1]));
            tris.push_back(QVector3D(tris[i][2], newPositionIndex + 2, newPositionIndex + 1));
            tris[i] = QVector3D(newPositionIndex + 0, newPositionIndex + 1, newPositionIndex + 2);
        }
    }

    // spherize
    for (vector<QVector3D>::iterator i = positions.begin();
         i != positions.end(); ++i)
    {
        (*i).normalize();
    }

    vector<vector<QVector3D>> meshData = {positions, tris};
    genMesh(meshData);
}
