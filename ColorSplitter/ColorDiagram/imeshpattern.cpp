#include "imeshpattern.h"

#include <QVector>
#include <QMatrix4x4>

/******************************************************************************
*   Паттерн меша для шкалы цветовой диаграммы
******************************************************************************/
ScalePartPattern::ScalePartPattern()
    : IMeshPattern()
{
    const QVector3D NORMAL_UP   ( 0.0f, 1.0f, 0.0f);
    const QVector3D NORMAL_DOWN ( 0.0f,-1.0f, 0.0f);
    const QVector3D NORMAL_LEFT (-1.0f, 0.0f, 0.0f);
    const QVector3D NORMAL_RIGHT( 1.0f, 0.0f, 0.0f);

    m_vertices.reserve(VERTICES_COORDINATES_COUNT);
    m_normals.reserve(VERTICES_COORDINATES_COUNT);

    QVector<QVector3D> baseVertices = {
        QVector3D{ INNER_R, SEMIHEIGHT, 0.0f },
        QVector3D{ INNER_R,-SEMIHEIGHT, 0.0f },
        QVector3D{ OUTER_R,-SEMIHEIGHT, 0.0f },
        QVector3D{ OUTER_R, SEMIHEIGHT, 0.0f }
    };

    QMatrix4x4 transform;
    transform.rotate(1.0f,UP);

    QVector<QVector3D> backVertices;
    for (QVector3D & point : baseVertices) {
        backVertices << transform.map(point);
    }
    transform.rotate(-1.0f,UP);
    QVector<QVector3D> frontVertices;
    for (QVector3D & point : baseVertices) {
        frontVertices << transform.map(point);
    }

    m_vertices = {
        /*top*/     backVertices[3].x(), backVertices[3].y(), backVertices[3].z(),
                    backVertices[0].x(), backVertices[0].y(), backVertices[0].z(),
                    frontVertices[0].x(), frontVertices[0].y(), frontVertices[0].z(),
                    frontVertices[3].x(), frontVertices[3].y(), frontVertices[3].z(),
        /*bottom*/  backVertices[1].x(), backVertices[1].y(), backVertices[1].z(),
                    backVertices[2].x(), backVertices[2].y(), backVertices[2].z(),
                    frontVertices[2].x(), frontVertices[2].y(), frontVertices[2].z(),
                    frontVertices[1].x(), frontVertices[1].y(), frontVertices[1].z(),
        /*left*/    backVertices[0].x(), backVertices[0].y(), backVertices[0].z(),
                    backVertices[1].x(), backVertices[1].y(), backVertices[1].z(),
                    frontVertices[1].x(), frontVertices[1].y(), frontVertices[1].z(),
                    frontVertices[0].x(), frontVertices[0].y(), frontVertices[0].z(),
        /*right*/   backVertices[2].x(), backVertices[2].y(), backVertices[2].z(),
                    backVertices[3].x(), backVertices[3].y(), backVertices[3].z(),
                    frontVertices[3].x(), frontVertices[3].y(), frontVertices[3].z(),
                    frontVertices[2].x(), frontVertices[2].y(), frontVertices[2].z()
    };
    m_normals = {
        /*top*/     NORMAL_UP.x(), NORMAL_UP.y(), NORMAL_UP.z(),
                    NORMAL_UP.x(), NORMAL_UP.y(), NORMAL_UP.z(),
                    NORMAL_UP.x(), NORMAL_UP.y(), NORMAL_UP.z(),
                    NORMAL_UP.x(), NORMAL_UP.y(), NORMAL_UP.z(),
        /*bottom*/  NORMAL_DOWN.x(), NORMAL_DOWN.y(), NORMAL_DOWN.z(),
                    NORMAL_DOWN.x(), NORMAL_DOWN.y(), NORMAL_DOWN.z(),
                    NORMAL_DOWN.x(), NORMAL_DOWN.y(), NORMAL_DOWN.z(),
                    NORMAL_DOWN.x(), NORMAL_DOWN.y(), NORMAL_DOWN.z(),
        /*left*/    NORMAL_LEFT.x(), NORMAL_LEFT.y(), NORMAL_LEFT.z(),
                    NORMAL_LEFT.x(), NORMAL_LEFT.y(), NORMAL_LEFT.z(),
                    NORMAL_LEFT.x(), NORMAL_LEFT.y(), NORMAL_LEFT.z(),
                    NORMAL_LEFT.x(), NORMAL_LEFT.y(), NORMAL_LEFT.z(),
        /*right*/   NORMAL_RIGHT.x(), NORMAL_RIGHT.y(), NORMAL_RIGHT.z(),
                    NORMAL_RIGHT.x(), NORMAL_RIGHT.y(), NORMAL_RIGHT.z(),
                    NORMAL_RIGHT.x(), NORMAL_RIGHT.y(), NORMAL_RIGHT.z(),
                    NORMAL_RIGHT.x(), NORMAL_RIGHT.y(), NORMAL_RIGHT.z()
    };
}


/******************************************************************************
*   Паттерн меша для цветовой диаграммы
******************************************************************************/
CubePattern::CubePattern()
{
    QVector<QVector3D> normals = {
        QVector3D { 0.0f, 1.0f, 0.0f}, // NORMAL_UP
        QVector3D { 0.0f,-1.0f, 0.0f}, // NORMAL_DOWN
        QVector3D {-1.0f, 0.0f, 0.0f}, // NORMAL_LEFT
        QVector3D { 1.0f, 0.0f, 0.0f}, // NORMAL_RIGHT
        QVector3D { 0.0f, 0.0f, 1.0f}, // NORMAL_FRONT
        QVector3D { 0.0f, 0.0f,-1.0f}  // NORMAL_BACK
    };

    m_vertices.reserve(VERTICES_COORDINATES_COUNT);
    m_normals.reserve(VERTICES_COORDINATES_COUNT);

    QVector<QVector3D> baseVertices = {
        QVector3D {-HALF_RIB,-HALF_RIB, HALF_RIB},
        QVector3D {-HALF_RIB, HALF_RIB, HALF_RIB},
        QVector3D { HALF_RIB, HALF_RIB, HALF_RIB},
        QVector3D { HALF_RIB,-HALF_RIB, HALF_RIB},
        QVector3D { HALF_RIB,-HALF_RIB,-HALF_RIB},
        QVector3D { HALF_RIB, HALF_RIB,-HALF_RIB},
        QVector3D {-HALF_RIB, HALF_RIB,-HALF_RIB},
        QVector3D {-HALF_RIB,-HALF_RIB,-HALF_RIB}
    };

    QVector<QVector<int>> faceIndices = {
        QVector<int> { 2, 5, 6, 1 }, // top
        QVector<int> { 7, 4, 3, 0 }, // bottom
        QVector<int> { 1, 6, 7, 0 }, // left
        QVector<int> { 4, 5, 2, 3 }, // right
        QVector<int> { 3, 2, 1, 0 }, // front
        QVector<int> { 7, 6, 5, 4 }  // back
    };

    for(auto & face : faceIndices) {
        for (int i = 0; i < VERTICES_PER_FACE; ++i) {
            m_vertices.push_back(baseVertices[face[i]].x());
            m_vertices.push_back(baseVertices[face[i]].y());
            m_vertices.push_back(baseVertices[face[i]].z());
        }
    }

    for(auto & normal : normals) {
        for (int i = 0; i < VERTICES_PER_FACE; ++i) {
            m_normals.push_back(normal.x());
            m_normals.push_back(normal.y());
            m_normals.push_back(normal.z());
        }
    }
}
