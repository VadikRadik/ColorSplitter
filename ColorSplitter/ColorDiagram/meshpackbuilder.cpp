#include "meshpackbuilder.h"

#include <QDebug>

MeshPackBuilder::MeshPackBuilder(std::shared_ptr<IMeshPattern> pattern,
                                 std::shared_ptr<QOpenGLShaderProgram> shader,
                                 GLenum drawMode, int patternsCount, int batchSize)
    : m_pattern(pattern)
    , m_lastPattern(patternsCount-1)
    , m_result(std::make_shared<MeshPack>())
    , m_shader(shader)
    , m_drawMode(drawMode)
    , m_batchMesh(std::make_shared<Mesh>(shader,drawMode))
    , m_meshBuilder(new MeshBuilder(m_pattern,batchSize))//m_pattern->patternDataSize()*batchSize))
    , m_currentPatternIndex(0)
    , m_meshBuilderSize(batchSize)//pattern->patternDataSize()*batchSize)
    , m_meshesForCreatingBuffer()
{

}


/******************************************************************************
*   Adds a geometry part to the mesh result
******************************************************************************/
void MeshPackBuilder::addPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    bool builderFilled = m_meshBuilder->addMeshByPattern(modelMatrix,color) || m_currentPatternIndex == m_lastPattern;
    if (builderFilled)
        addNewMeshBatch();

    m_currentPatternIndex++;
}


/******************************************************************************
*   Returns result
******************************************************************************/
std::shared_ptr<MeshPack> MeshPackBuilder::result() const
{
    qDebug() << m_result->meshesCount();
    return m_result;
}

void MeshPackBuilder::createMeshBuffersIfNeed()
{
    while (!m_meshesForCreatingBuffer.empty()) {

        std::shared_ptr<Mesh> topMesh = m_meshesForCreatingBuffer.top();

        topMesh->createBuffer();
        m_result->addMesh(topMesh);
        m_meshesForCreatingBuffer.pop();
    }
}


/******************************************************************************
*   Adds a mesh to the result
******************************************************************************/
void MeshPackBuilder::addNewMeshBatch()
{
    m_batchMesh->setVertices(m_meshBuilder->resultVertices());
    m_batchMesh->setNormals(m_meshBuilder->resultNormals());
    m_batchMesh->setColors(m_meshBuilder->resultColors());

    //m_batchMesh->createBuffer();

    //m_result->addMesh(m_batchMesh);
    // m
    m_meshesForCreatingBuffer.push(m_batchMesh);
    // m

    startNewBatch();
}


/******************************************************************************
*   Starts new mesh
******************************************************************************/
void MeshPackBuilder::startNewBatch()
{
    m_batchMesh = std::make_shared<Mesh>(m_shader, m_drawMode);
    m_meshBuilder.reset(new MeshBuilder(m_pattern,m_meshBuilderSize));
}
