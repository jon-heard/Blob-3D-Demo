
#include "algorithm_marchingcubes_calccubemesh.h"
#include <qDebug>

using namespace std;

vector<QVector3D> marchingCubes_calcCubeMesh(vector<int> activeControlPoints)
{
    vector<QVector3D> result;

    switch (activeControlPoints.size()) {
        case 1:
        {
            QVector3D controlVertex = CONTROL_POINT_VERTICES[activeControlPoints[0]];
            if (controlVertex[0] * controlVertex[1] * controlVertex[2] == 1)
            {
                result.push_back(controlVertex * QVector3D(0, 1, 1));
                result.push_back(controlVertex * QVector3D(1, 1, 0));
                result.push_back(controlVertex * QVector3D(1, 0, 1));
            } else {
                result.push_back(controlVertex * QVector3D(0, 1, 1));
                result.push_back(controlVertex * QVector3D(1, 0, 1));
                result.push_back(controlVertex * QVector3D(1, 1, 0));
            }
            break;
        }

        case 2:
        {
            QVector3D controlVertex1 = CONTROL_POINT_VERTICES[activeControlPoints[0]];
            QVector3D controlVertex2 = CONTROL_POINT_VERTICES[activeControlPoints[1]];
            int opposedAxis = -1;
            for (int i = 0; i < 3; ++i)
            {
                if (controlVertex1[i] != controlVertex2[i])
                {
                    if (opposedAxis == -1)
                    {
                        opposedAxis = i;
                    } else {
                        opposedAxis = -2;
                    }
                }
            }
            if (opposedAxis < 0)
            {
                vector<int> subControlPoints;
                vector<QVector3D> subResults;
                subControlPoints.push_back(activeControlPoints[0]);
                subResults = marchingCubes_calcCubeMesh(subControlPoints);
                result.insert(result.end(), subResults.begin(), subResults.end());
                subControlPoints.clear();
                subControlPoints.push_back(activeControlPoints[1]);
                subResults = marchingCubes_calcCubeMesh(subControlPoints);
                result.insert(result.end(), subResults.begin(), subResults.end());
            } else {
                int alignedAxis1 = 0;
                int alignedAxis2 = 1;
                if (opposedAxis == 0) { alignedAxis1 = 2; }
                if (opposedAxis == 1) { alignedAxis2 = 2; }
                QVector3D vertex;
                if ((controlVertex1[alignedAxis1] == controlVertex1[alignedAxis2] && opposedAxis == 2) ||
                    (controlVertex1[alignedAxis1] != controlVertex1[alignedAxis2] && opposedAxis != 2))
                {
                    vertex[opposedAxis] = -1;
                    vertex[alignedAxis1] = 0;
                    vertex[alignedAxis2] = controlVertex1[alignedAxis2];
                    result.push_back(vertex); //!!
                    vertex[alignedAxis1] = controlVertex1[alignedAxis1];
                    vertex[alignedAxis2] = 0;
                    result.push_back(vertex); //!!
                    vertex[opposedAxis] = 1;
                    result.push_back(vertex); //!!
                    result.push_back(vertex); //!!
                    vertex[alignedAxis1] = 0;
                    vertex[alignedAxis2] = controlVertex1[alignedAxis2];
                    result.push_back(vertex); //!!
                    vertex[opposedAxis] = -1;
                    result.push_back(vertex); //!!
                } else {
                    vertex[opposedAxis] = -1;
                    vertex[alignedAxis1] = controlVertex1[alignedAxis1];
                    vertex[alignedAxis2] = 0;
                    result.push_back(vertex); //!!
                    vertex[alignedAxis1] = 0;
                    vertex[alignedAxis2] = controlVertex1[alignedAxis2];
                    result.push_back(vertex); //!!
                    vertex[opposedAxis] = 1;
                    result.push_back(vertex); //!!
                    result.push_back(vertex); //!!
                    vertex[alignedAxis1] = controlVertex1[alignedAxis1];
                    vertex[alignedAxis2] = 0;
                    result.push_back(vertex); //!!
                    vertex[opposedAxis] = -1;
                    result.push_back(vertex); //!!
                }
            }
            break;
        }

        case 3:
        {
            QVector3D controlVertex1 = CONTROL_POINT_VERTICES[activeControlPoints[0]];
            QVector3D controlVertex2 = CONTROL_POINT_VERTICES[activeControlPoints[1]];
            QVector3D controlVertex3 = CONTROL_POINT_VERTICES[activeControlPoints[2]];

            int alignedAxis = -1;
            if (controlVertex1[0] == controlVertex2[0] && controlVertex1[0] == controlVertex2[0])
            {
                alignedAxis = 0;
            }
            else if (controlVertex1[1] == controlVertex2[1] && controlVertex1[1] == controlVertex2[1])
            {
                alignedAxis = 1;
            }
            else if (controlVertex1[2] == controlVertex2[2] && controlVertex1[2] == controlVertex2[2])
            {
                alignedAxis = 2;
            }

            if (alignedAxis != -1)
            {
                int opposedAxis1 = 0;
                int opposedAxis2 = 1;
                if (alignedAxis == 0) { opposedAxis1 = 2; }
                if (alignedAxis == 1) { opposedAxis2 = 2; }
                int direction1 = controlVertex1[opposedAxis1] + controlVertex2[opposedAxis1] + controlVertex3[opposedAxis1];
                int direction2 = controlVertex1[opposedAxis2] + controlVertex2[opposedAxis2] + controlVertex3[opposedAxis2];

                QVector3D vertex;
                vertex[alignedAxis] = 0;
                vertex[opposedAxis1] = controlVertex1[opposedAxis1];
                vertex[opposedAxis2] = controlVertex1[opposedAxis2];
                result.push_back(vertex);
                if (direction1 * direction2 * controlVertex1[alignedAxis] == 1)
                {
                    vertex[opposedAxis1] = controlVertex2[opposedAxis1];
                    vertex[opposedAxis2] = controlVertex2[opposedAxis2];
                    result.push_back(vertex);
                    vertex[opposedAxis1] = controlVertex3[opposedAxis1];
                    vertex[opposedAxis2] = controlVertex3[opposedAxis2];
                    result.push_back(vertex);
                } else {
                    vertex[opposedAxis1] = controlVertex3[opposedAxis1];
                    vertex[opposedAxis2] = controlVertex3[opposedAxis2];
                    result.push_back(vertex);
                    vertex[opposedAxis1] = controlVertex2[opposedAxis1];
                    vertex[opposedAxis2] = controlVertex2[opposedAxis2];
                    result.push_back(vertex);
                }
            } else {
                int opposedPoint = -1;
                if      (controlVertex1[0] == controlVertex2[0] && controlVertex1[1] == controlVertex2[1]) { opposedPoint = 2; }
                else if (controlVertex1[0] == controlVertex2[0] && controlVertex1[2] == controlVertex2[2]) { opposedPoint = 2; }
                else if (controlVertex1[1] == controlVertex2[1] && controlVertex1[2] == controlVertex2[2]) { opposedPoint = 2; }

                else if (controlVertex1[0] == controlVertex3[0] && controlVertex1[1] == controlVertex3[1]) { opposedPoint = 1; }
                else if (controlVertex1[0] == controlVertex3[0] && controlVertex1[2] == controlVertex3[2]) { opposedPoint = 1; }
                else if (controlVertex1[1] == controlVertex3[1] && controlVertex1[2] == controlVertex3[2]) { opposedPoint = 1; }

                else if (controlVertex2[0] == controlVertex3[0] && controlVertex2[1] == controlVertex3[1]) { opposedPoint = 0; }
                else if (controlVertex2[0] == controlVertex3[0] && controlVertex2[2] == controlVertex3[2]) { opposedPoint = 0; }
                else if (controlVertex2[1] == controlVertex3[1] && controlVertex2[2] == controlVertex3[2]) { opposedPoint = 0; }

                if (opposedPoint == -1) {
                    vector<int> subControlPoints;
                    vector<QVector3D> subResults;
                    subControlPoints.push_back(activeControlPoints[0]);
                    subResults = marchingCubes_calcCubeMesh(subControlPoints);
                    result.insert(result.end(), subResults.begin(), subResults.end());
                    subControlPoints.clear();
                    subControlPoints.push_back(activeControlPoints[1]);
                    subResults = marchingCubes_calcCubeMesh(subControlPoints);
                    result.insert(result.end(), subResults.begin(), subResults.end());
                    subControlPoints.clear();
                    subControlPoints.push_back(activeControlPoints[2]);
                    subResults = marchingCubes_calcCubeMesh(subControlPoints);
                    result.insert(result.end(), subResults.begin(), subResults.end());
                } else {
                    int alignedPoint1 = 0;
                    int alignedPoint2 = 1;
                    if (opposedPoint == 0) { alignedPoint1 = 2; }
                    if (opposedPoint == 1) { alignedPoint2 = 2; }
                    vector<int> subControlPoints;
                    vector<QVector3D> subResults;
                    subControlPoints.push_back(activeControlPoints[opposedPoint]);
                    subResults = marchingCubes_calcCubeMesh(subControlPoints);
                    result.insert(result.end(), subResults.begin(), subResults.end());
                    subControlPoints.clear();
                    subControlPoints.push_back(activeControlPoints[alignedPoint1]);
                    subControlPoints.push_back(activeControlPoints[alignedPoint2]);
                    subResults = marchingCubes_calcCubeMesh(subControlPoints);
                    result.insert(result.end(), subResults.begin(), subResults.end());
                }
            }
            break;
        }

        case 4:
        {
            QVector3D controlVertex1 = CONTROL_POINT_VERTICES[activeControlPoints[0]];
            QVector3D controlVertex2 = CONTROL_POINT_VERTICES[activeControlPoints[1]];
            QVector3D controlVertex3 = CONTROL_POINT_VERTICES[activeControlPoints[2]];
            QVector3D controlVertex4 = CONTROL_POINT_VERTICES[activeControlPoints[3]];
            int alignedAxis = -1;
            if (controlVertex1[0] == controlVertex2[0] && controlVertex1[0] == controlVertex3[0] && controlVertex1[0] == controlVertex4[0])
            {
                alignedAxis = 0;
            }
            else if (controlVertex1[1] == controlVertex2[1] && controlVertex1[1] == controlVertex3[1] && controlVertex1[1] == controlVertex4[1])
            {
                alignedAxis = 1;
            }
            else if (controlVertex1[2] == controlVertex2[2] && controlVertex1[2] == controlVertex3[2] && controlVertex1[2] == controlVertex4[2])
            {
                alignedAxis = 2;
            }
            if (alignedAxis != -1)
            {
                int opposedAxis1 = 0;
                int opposedAxis2 = 1;
                if (alignedAxis == 0) { opposedAxis1 = 2; }
                if (alignedAxis == 1) { opposedAxis2 = 2; }
                QVector3D vertex;
                vertex[alignedAxis] = 0;
                if ((alignedAxis != 2 && controlVertex1[alignedAxis] != 1) || (alignedAxis == 2 && controlVertex1[alignedAxis] == 1))
                {
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                } else {
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = -1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = 1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                    vertex[opposedAxis1] = -1;
                    vertex[opposedAxis2] = 1;
                    result.push_back(vertex);
                }
            }
            break;
        }
    }

    return result;
}
