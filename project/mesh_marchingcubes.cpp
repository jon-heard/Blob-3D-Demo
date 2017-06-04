
#include "mesh_marchingcubes.h"
#include <QOpenGLShaderProgram>
#include <vector>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

using namespace std;

Mesh_MarchingCubes::Mesh_MarchingCubes(QOpenGLShaderProgram* shader) : Mesh(shader)
{

}

Mesh_MarchingCubes::~Mesh_MarchingCubes() {}

bool Mesh_MarchingCubes::dirty()
{
    return _dirty;
}

void Mesh_MarchingCubes::setDirty(bool value)
{
    _dirty = value;
}

void Mesh_MarchingCubes::genMesh_MarchingCubes(Mesh_MarchingCubesData* predicate)
{
    if (vao != NULL)
    {
        vbo->destroy();
        vao->destroy();
        delete vbo;
        delete vao;
        vbo = NULL;
        vao = NULL;
    }
    if (predicate != NULL) {
        vector<QVector3D> positions({
                                        {-MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
                                        {MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
                                        {-MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
                                        {MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
                                        {-MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
                                        {MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
                                        {-MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
                                        {MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE}
                                    });
        vector<QVector3D> tris({
                                   {0, 1, 2}, {3, 2, 1}, // y-neg
                                   {4, 6, 5}, {7, 5, 6}, // y-pos
                                   {4, 0, 6}, {2, 6, 0}, // x-neg
                                   {5, 7, 1}, {3, 1, 7}, // x-pos
                                   {4, 5, 0}, {1, 0, 5}, // z-neg
                                   {6, 2, 7}, {3, 7, 2}  // z-pos
                               });
        vector<QVector3D>* meshData[] = {&positions, &tris};
        genMesh(meshData);
    }
}
