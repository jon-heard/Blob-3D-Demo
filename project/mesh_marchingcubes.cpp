
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
        BoundingBox bounds = parameters->MarchingCubes_getBounds();

        // bounding box render
//        vector<QVector3D> positions({
//                                        {bounds.low.x(), bounds.low.y(), bounds.low.z()},
//                                        {bounds.high.x(), bounds.low.y(), bounds.low.z()},
//                                        {bounds.low.x(), bounds.low.y(), bounds.high.z()},
//                                        {bounds.high.x(), bounds.low.y(), bounds.high.z()},
//                                        {bounds.low.x(), bounds.high.y(), bounds.low.z()},
//                                        {bounds.high.x(), bounds.high.y(), bounds.low.z()},
//                                        {bounds.low.x(), bounds.high.y(), bounds.high.z()},
//                                        {bounds.high.x(), bounds.high.y(), bounds.high.z()},
//                                    });
//        vector<QVector3D> tris({
//                                   {0, 1, 2}, {3, 2, 1}, // y-neg
//                                   {4, 6, 5}, {7, 5, 6}, // y-pos
//                                   {4, 0, 6}, {2, 6, 0}, // x-neg
//                                   {5, 7, 1}, {3, 1, 7}, // x-pos
//                                   {4, 5, 0}, {1, 0, 5}, // z-neg
//                                   {6, 2, 7}, {3, 7, 2}  // z-pos
//                               });

        vector<QVector3D> positions;
        vector<QVector3D> tris;
        for (float x = bounds.low.x(); x < bounds.high.x(); x += MARCHING_CUBE_SIZE)
        {
            for (float y = bounds.low.y(); y < bounds.high.y(); y += MARCHING_CUBE_SIZE)
            {
                for (float z = bounds.low.z(); z < bounds.high.z(); z += MARCHING_CUBE_SIZE)
                {
                    if (parameters->MarchingCubes_getIsWithin(QVector3D(x,y,z)))
                    {
                        int startIndex = positions.size();
                        positions.push_back(QVector3D(x-MARCHING_CUBE_SIZE, y-MARCHING_CUBE_SIZE, z-MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x+MARCHING_CUBE_SIZE, y-MARCHING_CUBE_SIZE, z-MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x-MARCHING_CUBE_SIZE, y-MARCHING_CUBE_SIZE, z+MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x+MARCHING_CUBE_SIZE, y-MARCHING_CUBE_SIZE, z+MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x-MARCHING_CUBE_SIZE, y+MARCHING_CUBE_SIZE, z-MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x+MARCHING_CUBE_SIZE, y+MARCHING_CUBE_SIZE, z-MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x-MARCHING_CUBE_SIZE, y+MARCHING_CUBE_SIZE, z+MARCHING_CUBE_SIZE));
                        positions.push_back(QVector3D(x+MARCHING_CUBE_SIZE, y+MARCHING_CUBE_SIZE, z+MARCHING_CUBE_SIZE));
                        tris.push_back(QVector3D(startIndex + 0, startIndex + 1, startIndex + 2));
                        tris.push_back(QVector3D(startIndex + 3, startIndex + 2, startIndex + 1));
                        tris.push_back(QVector3D(startIndex + 4, startIndex + 6, startIndex + 5));
                        tris.push_back(QVector3D(startIndex + 7, startIndex + 5, startIndex + 6));
                        tris.push_back(QVector3D(startIndex + 4, startIndex + 0, startIndex + 6));
                        tris.push_back(QVector3D(startIndex + 2, startIndex + 6, startIndex + 0));
                        tris.push_back(QVector3D(startIndex + 5, startIndex + 7, startIndex + 1));
                        tris.push_back(QVector3D(startIndex + 3, startIndex + 1, startIndex + 7));
                        tris.push_back(QVector3D(startIndex + 4, startIndex + 5, startIndex + 0));
                        tris.push_back(QVector3D(startIndex + 1, startIndex + 0, startIndex + 5));
                        tris.push_back(QVector3D(startIndex + 6, startIndex + 2, startIndex + 7));
                        tris.push_back(QVector3D(startIndex + 3, startIndex + 7, startIndex + 2));
                    }
                }
            }
        }

//        vector<QVector3D> positions({
//                                        {-MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
//                                        {MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
//                                        {-MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
//                                        {MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
//                                        {-MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
//                                        {MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, -MARCHING_CUBE_SIZE},
//                                        {-MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE},
//                                        {MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE, MARCHING_CUBE_SIZE}
//                                    });
//        vector<QVector3D> tris({
//                                   {0, 1, 2}, {3, 2, 1}, // y-neg
//                                   {4, 6, 5}, {7, 5, 6}, // y-pos
//                                   {4, 0, 6}, {2, 6, 0}, // x-neg
//                                   {5, 7, 1}, {3, 1, 7}, // x-pos
//                                   {4, 5, 0}, {1, 0, 5}, // z-neg
//                                   {6, 2, 7}, {3, 7, 2}  // z-pos
//                               });
        vector<QVector3D>* meshData[] = {&positions, &tris};
        genMesh(meshData);
    }
}
