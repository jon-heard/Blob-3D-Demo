
#include "mesh_marchingcubes.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "algorithm_marchingcubes_calccubemesh.h"

using namespace std;

Mesh_MarchingCubes::~Mesh_MarchingCubes() {}

bool Mesh_MarchingCubes::dirty() const
{
    return _dirty;
}

void Mesh_MarchingCubes::setDirty(bool value)
{
    _dirty = value;
}

void Mesh_MarchingCubes::genMesh_BoundingBox(Mesh_MarchingCubesParameters* parameters)
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

    if (parameters != NULL) {
        BoundingBox bounds = parameters->Mesh_MarchingCubeParameters_getBounds();
        vector<QVector3D> positions({
                                        {bounds.low.x(), bounds.low.y(), bounds.low.z()},
                                        {bounds.high.x(), bounds.low.y(), bounds.low.z()},
                                        {bounds.low.x(), bounds.low.y(), bounds.high.z()},
                                        {bounds.high.x(), bounds.low.y(), bounds.high.z()},
                                        {bounds.low.x(), bounds.high.y(), bounds.low.z()},
                                        {bounds.high.x(), bounds.high.y(), bounds.low.z()},
                                        {bounds.low.x(), bounds.high.y(), bounds.high.z()},
                                        {bounds.high.x(), bounds.high.y(), bounds.high.z()},
                                    });
        vector<QVector3D> tris({
                                   {0, 1, 2}, {3, 2, 1}, // y-neg
                                   {4, 6, 5}, {7, 5, 6}, // y-pos
                                   {4, 0, 6}, {2, 6, 0}, // x-neg
                                   {5, 7, 1}, {3, 1, 7}, // x-pos
                                   {4, 5, 0}, {1, 0, 5}, // z-neg
                                   {6, 2, 7}, {3, 7, 2}  // z-pos
                               });
    }
}

void Mesh_MarchingCubes::genMesh_MarchingCubes(Mesh_MarchingCubesParameters* parameters)
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
    if (parameters != NULL) {
        BoundingBox bounds = parameters->Mesh_MarchingCubeParameters_getBounds();
        //bounds.low *= 2;
        //bounds.high *= 2;

        vector<QVector3D> positions;
        vector<QVector3D> tris;
        for (float x = bounds.low.x(); x < bounds.high.x(); x += MARCHING_CUBE_SIZE)
        {
            for (float y = bounds.low.y(); y < bounds.high.y(); y += MARCHING_CUBE_SIZE)
            {
                for (float z = bounds.low.z(); z < bounds.high.z(); z += MARCHING_CUBE_SIZE)
                {
                    vector<int> activeControlPoints;
                    for (int i = 0; i < 8; ++i) {
                        if(parameters->Mesh_MarchingCubeParameters_getIsWithin(QVector3D(
                                x + MARCHING_CUBE_SIZE * CONTROL_POINT_VERTICES[i][0],
                                y + MARCHING_CUBE_SIZE * CONTROL_POINT_VERTICES[i][1],
                                z + MARCHING_CUBE_SIZE * CONTROL_POINT_VERTICES[i][2])))
                        {
                            activeControlPoints.push_back(i);
                        }
                    }
                    if (activeControlPoints.size() > 0 && activeControlPoints.size() < 8)
                    {
                        vector<QVector3D> cubeMesh = marchingCubes_calcCubeMesh(activeControlPoints);
                        addVectorsToMesh(QVector3D(x,y,z), cubeMesh, positions, tris);
                    }
                }
            }
        }

        vector<vector<QVector3D>> meshData = {positions, tris};
        genMesh(meshData);
    }
}

void Mesh_MarchingCubes::addVectorsToMesh(QVector3D offset, vector<QVector3D> vertices, vector<QVector3D>& positions, vector<QVector3D>& tris)
{
    unsigned int startIndex = (unsigned int)positions.size();
    for (int i = 0; i < vertices.size(); ++i) {
        positions.push_back(offset + MARCHING_CUBE_SIZE * vertices[i]);
    }
    for (int i = 0; i < vertices.size(); i += 3) {
        tris.push_back(QVector3D(i + startIndex + 0, i + startIndex + 1, i + startIndex + 2));
    }
}
