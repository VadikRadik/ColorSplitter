#include "meshbuilder.h"

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

MeshBuilder::MeshBuilder(std::shared_ptr<IMeshPattern> pattern, int builderSize)
    : m_patternVertices()
    , m_patternNormals()
    , m_resultVertices()
    , m_resultNormals()
    , m_resultColors()
    , m_batchFloatsSize(builderSize)
    , m_patternFloatsCount(0)
{
    /*QVector<GLfloat> vertices;
    vertices
    <<-0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f
    <<-0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f
    <<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f
    << 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f
    <<-0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<< 0.5f<<-0.5f<<-0.5f<<-0.5f
    <<-0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<< 0.5f<<-0.5f<< 0.5f<<-0.5f;
    m_patternVertices = vertices.toStdVector();

    QVector<GLfloat> normals;
    normals
    << 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f
    << 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f
    <<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f
    << 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f
    << 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f<< 0.0f<<-1.0f<< 0.0f
    << 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f;
    m_patternNormals = normals.toStdVector();

    QVector<GLfloat> colors;
    colors
    << 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f
    << 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f
    << 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f
    << 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f
    << 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f
    << 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f<< 0.0f<< 1.0f<< 0.0f;
    m_patternColors = colors.toStdVector();

    m_resultVertices = m_patternVertices;
    m_resultNormals = m_patternNormals;
    m_resultColors = m_patternColors;*/
    m_patternVertices = pattern->vertices();
    m_patternNormals = pattern->normals();
    m_patternFloatsCount = m_patternVertices.size();

    m_resultVertices.reserve(m_batchFloatsSize);
    m_resultNormals.reserve(m_batchFloatsSize);
    m_resultColors.reserve(m_batchFloatsSize);
}


/******************************************************************************
*   Добавление к мешу паттерна в определённое место и с определёнными цветами
*   Возвращает состояние заполненности до конца
******************************************************************************/
bool MeshBuilder::addMeshByPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    float red = qRed(color)/255.0f;
    float green = qGreen(color)/255.0f;
    float blue = qBlue(color)/255.0f;

    for (unsigned int i = 0; i < m_patternVertices.size(); i += 3) {
        QVector3D newMeshVertex = modelMatrix.map(QVector3D(m_patternVertices.at(i),m_patternVertices.at(i+1),m_patternVertices.at(i+2)));
        m_resultVertices.push_back(newMeshVertex.x());
        m_resultVertices.push_back(newMeshVertex.y());
        m_resultVertices.push_back(newMeshVertex.z());

        QVector3D newMeshNormal = modelMatrix.mapVector(QVector3D(m_patternNormals.at(i),m_patternNormals.at(i+1),m_patternNormals.at(i+2)));
        newMeshNormal.normalize();
        m_resultNormals.push_back(newMeshNormal.x());
        m_resultNormals.push_back(newMeshNormal.y());
        m_resultNormals.push_back(newMeshNormal.z());

        m_resultColors.push_back(red);
        m_resultColors.push_back(green);
        m_resultColors.push_back(blue);
    }

    return m_resultVertices.size() + m_patternFloatsCount > m_batchFloatsSize;
}


/******************************************************************************
*   Координаты вершин для перемещения в буфер меша
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultVertices()
{
    return m_resultVertices;
}


/******************************************************************************
*   Координаты нормалей для перемещения в буфер меша
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultNormals()
{
    return m_resultNormals;
}


/******************************************************************************
*   Компоненты цветов для перемещения в буфер меша
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultColors()
{
    return m_resultColors;
}
