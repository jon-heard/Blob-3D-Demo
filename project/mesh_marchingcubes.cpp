
#include "mesh_marchingcubes.h"
#include <QOpenGLShaderProgram>
#include <vector>

using namespace std;

Mesh_MarchingCubes::Mesh_MarchingCubes(QOpenGLShaderProgram* shader) : Mesh(shader)
{

}

Mesh_MarchingCubes::~Mesh_MarchingCubes() {}

void Mesh_MarchingCubes::genMesh_MarchingCubes(Mesh_MarchingCubesData* predicate)
{
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

    vector<QVector3D>* meshData[] = {&positions, &tris};
    genMesh(meshData);
}
