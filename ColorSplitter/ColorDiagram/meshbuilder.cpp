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
    m_patternVertices = pattern->vertices();
    m_patternNormals = pattern->normals();
    m_patternFloatsCount = m_patternVertices.size();

    m_resultVertices.reserve(m_batchFloatsSize);
    m_resultNormals.reserve(m_batchFloatsSize);
    m_resultColors.reserve(m_batchFloatsSize);
}


/******************************************************************************
*   Adds mesh patrts by pattern and returns filled state
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
*   Vertex coordinates for moving to the mesh
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultVertices()
{
    return m_resultVertices;
}


/******************************************************************************
*   Vertex normals coordinates for moving to the mesh
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultNormals()
{
    return m_resultNormals;
}


/******************************************************************************
*   Vertex color components for moving to the mesh
******************************************************************************/
std::vector<GLfloat> &MeshBuilder::resultColors()
{
    return m_resultColors;
}
