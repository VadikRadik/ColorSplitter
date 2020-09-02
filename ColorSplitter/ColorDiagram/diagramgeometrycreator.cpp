#include "diagramgeometrycreator.h"

#include <QtMath>

DiagramGeometryCreator::DiagramGeometryCreator(std::vector<std::pair<QRgb, int>> &colors,
                                                 std::shared_ptr<IMeshPattern> pattern,
                                                 int batchSize)
    : m_pattern(pattern)
    , m_meshesForCreatingBuffer()
    , m_resultMeshes()
    , m_meshBuilder(new MeshBuilder(m_pattern,batchSize))
    , m_lastPatternIndex(colors.size()-1)
    , m_currentPatternIndex(0)
    , m_drawMode(pattern->drawMode())
    , m_meshBuilderSize(batchSize)
    , m_batchMesh(std::make_shared<Mesh>(nullptr,m_drawMode))
    , m_resultMutex()
    , m_bufferStackMutex()
    , m_isCreatingFinished()
    , m_colors(std::move(colors))
{
    m_isCreatingFinished.store(false);
}


/******************************************************************************
*   Returns a result mesh
******************************************************************************/
std::list<std::shared_ptr<Mesh>> DiagramGeometryCreator::resultMeshes() const
{
    std::lock_guard<std::mutex> lock(m_resultMutex);
    return m_resultMeshes;
}


/******************************************************************************
*   Checks for creating finish from the main thread
******************************************************************************/
bool DiagramGeometryCreator::isCreatingFininshed() const
{
    return m_isCreatingFinished.load();
}


/******************************************************************************
*   Called from main thread and current OpenGL context
*   for creating vertex buffers for new meshes
******************************************************************************/
void DiagramGeometryCreator::createMeshBuffersIfNeed()
{
    while (!m_meshesForCreatingBuffer.empty()) {
        m_bufferStackMutex.lock();
        std::shared_ptr<Mesh> topMesh = m_meshesForCreatingBuffer.top();
        m_meshesForCreatingBuffer.pop();
        m_bufferStackMutex.unlock();

        topMesh->createBuffer();
    }
}


/******************************************************************************
*   Starts creating meshes
******************************************************************************/
void DiagramGeometryCreator::startCreation()
{
    for (auto it = m_colors.cbegin(); it != m_colors.cend(); ++it) {
        QColor clrHsv = QColor(it->first).toHsv();

        QMatrix4x4 model;
        model.rotate(clrHsv.hsvHue(),UP);
        model.translate(clrHsv.saturationF(),clrHsv.valueF(),0.0f);
        model.scale(qPow(it->second,VOLUME_POWER) * DIAGRAM_POINT_SCALE_FACTOR);

        addPattern(model,it->first);
    }
    m_isCreatingFinished.store(true);
}


/******************************************************************************
*   Adds a geometry part to the mesh result
******************************************************************************/
void DiagramGeometryCreator::addPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    bool builderFilled = m_meshBuilder->addMeshByPattern(modelMatrix,color) || m_currentPatternIndex == m_lastPatternIndex;
    if (builderFilled)
        addNewMeshBatch();

    ++m_currentPatternIndex;
}


/******************************************************************************
*   Adds a mesh to the result
******************************************************************************/
void DiagramGeometryCreator::addNewMeshBatch()
{
    m_batchMesh->setVertices(m_meshBuilder->resultVertices());
    m_batchMesh->setNormals(m_meshBuilder->resultNormals());
    m_batchMesh->setColors(m_meshBuilder->resultColors());

    m_bufferStackMutex.lock();
    m_meshesForCreatingBuffer.push(m_batchMesh);
    m_bufferStackMutex.unlock();

    m_resultMutex.lock();
    m_resultMeshes.push_back(m_batchMesh);
    m_resultMutex.unlock();

    startNewBatch();
}


/******************************************************************************
*   Starts a new mesh
******************************************************************************/
void DiagramGeometryCreator::startNewBatch()
{
    m_batchMesh = std::make_shared<Mesh>(nullptr, m_drawMode);
    m_meshBuilder.reset(new MeshBuilder(m_pattern,m_meshBuilderSize));
}
