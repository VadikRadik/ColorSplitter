#include "meshpackbuilder.h"

MeshPackBuilder::MeshPackBuilder(std::shared_ptr<IMeshPattern> pattern,
                                 std::shared_ptr<QOpenGLShaderProgram> shader,
                                 GLenum drawMode, int patternsCount, int batchSize)
    : m_pattern(pattern)
    , m_lastPattern(patternsCount-1)
    , m_result(std::make_shared<MeshPack>())
    , m_shader(shader)
    , m_drawMode(drawMode)
    , m_batchMesh(std::make_shared<Mesh>(shader,drawMode))
    , m_meshBuilder(new MeshBuilder(m_pattern,m_pattern->patternDataSize()*batchSize))
    , m_currentPatternIndex(0)
    , m_meshBuilderSize(pattern->patternDataSize()*batchSize)
{

}

void MeshPackBuilder::addPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    bool builderFilled = m_meshBuilder->addMeshByPattern(modelMatrix,color) || m_currentPatternIndex == m_lastPattern;
    if (builderFilled)
        addNewMeshBatch();

    m_currentPatternIndex++;
}

std::shared_ptr<MeshPack> MeshPackBuilder::result() const
{
    return m_result;
}

void MeshPackBuilder::addNewMeshBatch()
{
    m_batchMesh->setVertices(m_meshBuilder->resultVertices());
    m_batchMesh->setNormals(m_meshBuilder->resultNormals());
    m_batchMesh->setColors(m_meshBuilder->resultColors());

    m_batchMesh->createBuffer();

    m_result->addMesh(m_batchMesh);

    startNewBatch();
}

void MeshPackBuilder::startNewBatch()
{
    m_batchMesh = std::make_shared<Mesh>(m_shader, m_drawMode);
    m_meshBuilder.reset(new MeshBuilder(m_pattern,m_meshBuilderSize));
}
