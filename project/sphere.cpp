
#include "sphere.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDebug>

using namespace std;

int Sphere::instanceCount = 0;
QOpenGLBuffer* Sphere::sphereVbo = NULL;
QOpenGLVertexArrayObject* Sphere::sphereVao = NULL;
int Sphere::sphereVertexCount = 0;

Sphere::Sphere(QOpenGLShaderProgram* shader) : Mesh(shader)
{
    if (instanceCount == 0)
    {
        genSphereMesh();
        Sphere::sphereVbo = vbo;
        Sphere::sphereVao = vao;
        Sphere::sphereVertexCount = vertexCount;
    } else {
        vbo = Sphere::sphereVbo;
        vao = Sphere::sphereVao;
        vertexCount = Sphere::sphereVertexCount;
    }
    ++instanceCount;
}

Sphere::~Sphere()
{
    --instanceCount;
    if (instanceCount == 0)
    {
        vbo->destroy();
        vao->destroy();
        delete vbo;
        delete vao;
    }
}

void Sphere::genSphereMesh()
{
    // Setup initial icosphere (a cube)
    vector<QVector3D> positions({
                                    {-.5, -.5, -.5},
                                    {.5, -.5, -.5},
                                    {-.5, -.5, .5},
                                    {.5, -.5, .5},
                                    {-.5, .5, -.5},
                                    {.5, .5, -.5},
                                    {-.5, .5, .5},
                                    {.5, .5, .5}
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
    for (int i = 0; i < positions.size(); ++i)
    {
        positions[i].normalize();
    }

    // voltage data (single value for entire mesh)
    vector<QVector3D> voltage;
    for (int i = 0; i < positions.size(); ++i)
    {
        voltage.push_back(QVector3D(1,1,1));
    }

    vector<QVector3D>* meshData[] = {&positions, &tris, &voltage};
    genMesh(meshData);
}
