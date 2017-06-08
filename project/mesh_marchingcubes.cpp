
#include "mesh_marchingcubes.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

using namespace std;

const int CORNERS[8][3] = {
    {-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1},
    {+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}
};

Mesh_MarchingCubes::Mesh_MarchingCubes(QOpenGLShaderProgram* shader) : Mesh(shader)
{

}

Mesh_MarchingCubes::~Mesh_MarchingCubes() {}

bool Mesh_MarchingCubes::dirty() const
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
        //bounds.low *= 2;
        //bounds.high *= 2;

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
                    vector<QVector3D> hits;
                    for (int i = 0; i < 8; ++i) {
                        if (parameters->MarchingCubes_getIsWithin(QVector3D(
                                                                      x + MARCHING_CUBE_SIZE * CORNERS[i][0],
                                                                      y + MARCHING_CUBE_SIZE * CORNERS[i][1],
                                                                      z + MARCHING_CUBE_SIZE * CORNERS[i][2])))
                        {
                            hits.push_back(QVector3D(CORNERS[i][0], CORNERS[i][1], CORNERS[i][2]));
                        }
                    }
                    if (hits.size() > 0 && hits.size() < 8)
                    {
                        addCubeToMesh(hits, QVector3D(x,y,z), positions, tris);
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

void Mesh_MarchingCubes::addCubeToMesh(vector<QVector3D> hits, QVector3D position, vector<QVector3D>& positions, vector<QVector3D>& tris)
{
    vector<QVector3D> vertices;
    int opposedAxis = -1;

    switch (hits.size()) {
    case 1:
        if (hits[0][0] * hits[0][1] * hits[0][2] == 1)
        {
            vertices.push_back(hits[0] * QVector3D(0, 1, 1));
            vertices.push_back(hits[0] * QVector3D(1, 1, 0));
            vertices.push_back(hits[0] * QVector3D(1, 0, 1));
        } else {
            vertices.push_back(hits[0] * QVector3D(0, 1, 1));
            vertices.push_back(hits[0] * QVector3D(1, 0, 1));
            vertices.push_back(hits[0] * QVector3D(1, 1, 0));
        }
        break;
    case 2:
        for (int i = 0; i < 3; ++i) {
            if (hits[0][i] != hits[1][i]) {
                if (opposedAxis == -1) {
                    opposedAxis = i;
                } else {
                    opposedAxis = -2;
                }
            }
        }
        if (opposedAxis == -2) {
            vector<QVector3D> subHits;
            subHits.push_back(hits[0]);
            addCubeToMesh(subHits, position, positions, tris);
            subHits[0] = hits[1];
            addCubeToMesh(subHits, position, positions, tris);
        } else {
            int alignedAxis1 = 0;
            int alignedAxis2 = 1;
            if (opposedAxis == 0) { alignedAxis1 = 2; }
            if (opposedAxis == 1) { alignedAxis2 = 2; }

            QVector3D vertex;
            if ((hits[0][alignedAxis1] == hits[0][alignedAxis2] && opposedAxis == 2) ||
                (hits[0][alignedAxis1] != hits[0][alignedAxis2] && opposedAxis != 2))
            {
                vertex[opposedAxis] = -1;
                vertex[alignedAxis1] = 0;
                vertex[alignedAxis2] = hits[0][alignedAxis2];
                vertices.push_back(vertex); //!!
                vertex[alignedAxis1] = hits[0][alignedAxis1];
                vertex[alignedAxis2] = 0;
                vertices.push_back(vertex); //!!
                vertex[opposedAxis] = 1;
                vertices.push_back(vertex); //!!
                vertices.push_back(vertex); //!!
                vertex[alignedAxis1] = 0;
                vertex[alignedAxis2] = hits[0][alignedAxis2];
                vertices.push_back(vertex); //!!
                vertex[opposedAxis] = -1;
                vertices.push_back(vertex); //!!
            } else {
                vertex[opposedAxis] = -1;
                vertex[alignedAxis1] = hits[0][alignedAxis1];
                vertex[alignedAxis2] = 0;
                vertices.push_back(vertex); //!!
                vertex[alignedAxis1] = 0;
                vertex[alignedAxis2] = hits[0][alignedAxis2];
                vertices.push_back(vertex); //!!
                vertex[opposedAxis] = 1;
                vertices.push_back(vertex); //!!
                vertices.push_back(vertex); //!!
                vertex[alignedAxis1] = hits[0][alignedAxis1];
                vertex[alignedAxis2] = 0;
                vertices.push_back(vertex); //!!
                vertex[opposedAxis] = -1;
                vertices.push_back(vertex); //!!
            }
        }
        break;
    case 3:
        opposedAxis = -1;
        if (hits[0][0] == hits[1][0] && hits[0][0] == hits[2][0]) { opposedAxis = 0; }
        else if (hits[0][1] == hits[1][1] && hits[0][1] == hits[2][1]) { opposedAxis = 1; }
        else if (hits[0][2] == hits[1][2] && hits[0][2] == hits[2][2]) { opposedAxis = 2; }

        if (opposedAxis != -1)
        {
            int alignedAxis1 = 0;
            int alignedAxis2 = 1;
            if (opposedAxis == 0) { alignedAxis1 = 2; }
            if (opposedAxis == 1) { alignedAxis2 = 2; }
            int direction1 = hits[0][alignedAxis1] + hits[1][alignedAxis1] + hits[2][alignedAxis1];
            int direction2 = hits[0][alignedAxis2] + hits[1][alignedAxis2] + hits[2][alignedAxis2];

            QVector3D vertex;
            vertex[opposedAxis] = 0;
            vertex[alignedAxis1] = hits[0][alignedAxis1];
            vertex[alignedAxis2] = hits[0][alignedAxis2];
            vertices.push_back(vertex);
            if (direction1 * direction2 * hits[0][opposedAxis] == 1)
            {
                vertex[alignedAxis1] = hits[1][alignedAxis1];
                vertex[alignedAxis2] = hits[1][alignedAxis2];
                vertices.push_back(vertex);
                vertex[alignedAxis1] = hits[2][alignedAxis1];
                vertex[alignedAxis2] = hits[2][alignedAxis2];
                vertices.push_back(vertex);
            } else {
                vertex[alignedAxis1] = hits[2][alignedAxis1];
                vertex[alignedAxis2] = hits[2][alignedAxis2];
                vertices.push_back(vertex);
                vertex[alignedAxis1] = hits[1][alignedAxis1];
                vertex[alignedAxis2] = hits[1][alignedAxis2];
                vertices.push_back(vertex);
            }
        } else {
            int opposedHit = -1;
            if      (hits[0][0] == hits[1][0] && hits[0][1] == hits[1][1]) { opposedHit = 2; }
            else if (hits[0][0] == hits[1][0] && hits[0][2] == hits[1][2]) { opposedHit = 2; }
            else if (hits[0][1] == hits[1][1] && hits[0][2] == hits[1][2]) { opposedHit = 2; }

            else if (hits[0][0] == hits[2][0] && hits[0][1] == hits[2][1]) { opposedHit = 1; }
            else if (hits[0][0] == hits[2][0] && hits[0][2] == hits[2][2]) { opposedHit = 1; }
            else if (hits[0][1] == hits[2][1] && hits[0][2] == hits[2][2]) { opposedHit = 1; }

            else if (hits[1][0] == hits[2][0] && hits[1][1] == hits[2][1]) { opposedHit = 0; }
            else if (hits[1][0] == hits[2][0] && hits[1][2] == hits[2][2]) { opposedHit = 0; }
            else if (hits[1][1] == hits[2][1] && hits[1][2] == hits[2][2]) { opposedHit = 0; }

            if (opposedHit != -1) {
                int alignedHit1 = 0;
                int alignedHit2 = 1;
                if (opposedHit == 0) { alignedHit1 = 2; }
                if (opposedHit == 1) { alignedHit2 = 2; }
                vector<QVector3D> subHits;
                subHits.push_back(hits[opposedHit]);
                addCubeToMesh(subHits, position, positions, tris);
                subHits.clear();
                subHits.push_back(hits[alignedHit1]);
                subHits.push_back(hits[alignedHit2]);
                addCubeToMesh(subHits, position, positions, tris);
            } else {
                vector<QVector3D> subHits;
                subHits.push_back(hits[0]);
                addCubeToMesh(subHits, position, positions, tris);
                subHits.clear();
                subHits.push_back(hits[1]);
                addCubeToMesh(subHits, position, positions, tris);
                subHits.clear();
                subHits.push_back(hits[2]);
                addCubeToMesh(subHits, position, positions, tris);
            }
        }
        break;
    case 4:
        opposedAxis = -1;
        if      (hits[0][0] == hits[1][0] && hits[0][0] == hits[2][0] && hits[0][0] == hits[3][0]) { opposedAxis = 0; }
        else if (hits[0][1] == hits[1][1] && hits[0][1] == hits[2][1] && hits[0][1] == hits[3][1]) { opposedAxis = 1; }
        else if (hits[0][2] == hits[1][2] && hits[0][2] == hits[2][2] && hits[0][2] == hits[3][2]) { opposedAxis = 2; }
        if (opposedAxis != -1)
        {
            int alignedAxis1 = 0;
            int alignedAxis2 = 1;
            if (opposedAxis == 0) { alignedAxis1 = 2; }
            if (opposedAxis == 1) { alignedAxis2 = 2; }
            QVector3D vertex;
            vertex[opposedAxis] = 0;
            if ((opposedAxis != 2 && hits[0][opposedAxis] != 1) || (opposedAxis == 2 && hits[0][opposedAxis] == 1))
            {
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
            } else {
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = -1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = 1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
                vertex[alignedAxis1] = -1;
                vertex[alignedAxis2] = 1;
                vertices.push_back(vertex);
            }
        }
        break;
    }

//    switch(cubeType)
//    {
//    // 1 tri
//    case 1:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));
//    break;
//    case 2:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(-1, -1, 0));
//    break;
//    case 4:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(0, +1, -1));  vertices.push_back(QVector3D(-1, +1, 0));
//    break;
//    case 8:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(-1, +1, 0));  vertices.push_back(QVector3D(0, +1, +1));
//    break;
//    case 16:
//        vertices.push_back(QVector3D(+1, 0, -1));  vertices.push_back(QVector3D(0, -1, -1));  vertices.push_back(QVector3D(+1, -1, 0));
//    break;
//    case 32:
//        vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(+1, -1, 0));  vertices.push_back(QVector3D(0, -1, +1));
//    break;
//    case 64:
//        vertices.push_back(QVector3D(+1, 0, -1));  vertices.push_back(QVector3D(+1, +1, 0));  vertices.push_back(QVector3D(0, +1, -1));
//    break;
//    case 128:
//        vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(0, +1, +1));  vertices.push_back(QVector3D(+1, +1, 0));
//    break;

//    // 2 tri
//    case 3:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, -1));
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(0, -1, -1));
//    break;
//    case 5:
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));  vertices.push_back(QVector3D(0, 1, -1));
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, 1, -1));  vertices.push_back(QVector3D(-1, 1, 0));
//    break;
//    case 9:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(-1, +1, 0));  vertices.push_back(QVector3D(0, +1, +1));
//    break;
//    case 17:
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(1, 0, -1));  vertices.push_back(QVector3D(-1, 0, -1));
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(1, -1, 0));  vertices.push_back(QVector3D(1, 0, -1));
//    break;
//    case 33:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));
//        vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(+1, -1, 0));  vertices.push_back(QVector3D(0, -1, +1));
//    break;
//    case 65:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));
//        vertices.push_back(QVector3D(+1, 0, -1));  vertices.push_back(QVector3D(+1, +1, 0));  vertices.push_back(QVector3D(0, +1, -1));
//    break;
//    case 129:
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, -1, -1));
//        vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(0, +1, +1));  vertices.push_back(QVector3D(+1, +1, 0));
//    break;
//    case 6:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(-1, -1, 0));
//        vertices.push_back(QVector3D(-1, 0, -1));  vertices.push_back(QVector3D(0, +1, -1));  vertices.push_back(QVector3D(-1, +1, 0));
//    break;
//    case 10:
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(0, +1, +1));  vertices.push_back(QVector3D(0, -1, +1));
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(-1, +1, 0));  vertices.push_back(QVector3D(0, +1, +1));
//    break;
//    case 18:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(-1, -1, 0));
//        vertices.push_back(QVector3D(+1, 0, -1));  vertices.push_back(QVector3D(0, -1, -1));  vertices.push_back(QVector3D(+1, -1, 0));
//    break;
//    case 34:
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(+1, 0, +1));
//        vertices.push_back(QVector3D(-1, -1, 0));  vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(+1, -1, 0));
//    break;
//    case 66:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(-1, -1, 0));
//        vertices.push_back(QVector3D(+1, 0, -1));  vertices.push_back(QVector3D(+1, +1, 0));  vertices.push_back(QVector3D(0, +1, -1));
//    break;
//    case 130:
//        vertices.push_back(QVector3D(-1, 0, +1));  vertices.push_back(QVector3D(0, -1, +1));  vertices.push_back(QVector3D(-1, -1, 0));
//        vertices.push_back(QVector3D(+1, 0, +1));  vertices.push_back(QVector3D(0, +1, +1));  vertices.push_back(QVector3D(+1, +1, 0));
//    break;
//    }

//    vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(+1, -1, -1));  vertices.push_back(QVector3D(-1, -1, +1));
//    vertices.push_back(QVector3D(+1, -1, +1));  vertices.push_back(QVector3D(-1, -1, +1));  vertices.push_back(QVector3D(+1, -1, -1));
//    vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(-1, -1, -1));
//    vertices.push_back(QVector3D(+1, +1, +1));  vertices.push_back(QVector3D(+1, +1, -1));  vertices.push_back(QVector3D(-1, +1, +1));
//    vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(-1, -1, -1));
//    vertices.push_back(QVector3D(-1, -1, +1));  vertices.push_back(QVector3D(-1, +1, +1));  vertices.push_back(QVector3D(-1, -1, 01));
//    vertices.push_back(QVector3D(+1, +1, -1));  vertices.push_back(QVector3D(+1, +1, +1));  vertices.push_back(QVector3D(+1, -1, -1));
//    vertices.push_back(QVector3D(+1, -1, +1));  vertices.push_back(QVector3D(+1, -1, -1));  vertices.push_back(QVector3D(+1, +1, +1));
//    vertices.push_back(QVector3D(-1, +1, -1));  vertices.push_back(QVector3D(+1, +1, -1));  vertices.push_back(QVector3D(-1, -1, -1));
//    vertices.push_back(QVector3D(+1, -1, -1));  vertices.push_back(QVector3D(-1, -1, -1));  vertices.push_back(QVector3D(+1, +1, -1));
//    vertices.push_back(QVector3D(-1, +1, +1));  vertices.push_back(QVector3D(-1, -1, +1));  vertices.push_back(QVector3D(+1, +1, +1));
//    vertices.push_back(QVector3D(+1, -1, +1));  vertices.push_back(QVector3D(+1, +1, +1));  vertices.push_back(QVector3D(-1, -1, +1));

    addVectorsToMesh(position, vertices, positions, tris);
}

