#ifndef ALGORITHM_MARCHINGCUBES_CALCCUBEMESH_H
#define ALGORITHM_MARCHINGCUBES_CALCCUBEMESH_H

#include <vector>
#include <QVector3D>

const QVector3D CONTROL_POINT_VERTICES[8] = {
    {-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1},
    {+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}
};

std::vector<QVector3D> marchingCubes_calcCubeMesh(std::vector<int> activeControlPoints);

#endif // ALGORITHM_MARCHINGCUBES_CALCCUBEMESH_H
