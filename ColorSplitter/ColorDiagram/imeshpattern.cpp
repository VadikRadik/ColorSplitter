#include "imeshpattern.h"

#include <QVector>
#include <QMatrix4x4>

/******************************************************************************
*   Паттерн меша для цветовой диаграммы
******************************************************************************/
ScalePartPattern::ScalePartPattern()
    : IMeshPattern()
{
    const QVector3D NORMAL_UP   ( 0.0f, 1.0f, 0.0f);
    const QVector3D NORMAL_DOWN ( 0.0f,-1.0f, 0.0f);
    const QVector3D NORMAL_LEFT (-1.0f, 0.0f, 0.0f);
    const QVector3D NORMAL_RIGHT( 1.0f, 0.0f, 0.0f);

    m_vertices.reserve(VERTICES_COUNT);
    m_normals.reserve(VERTICES_COUNT);

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
