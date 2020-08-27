#include "meshpackbuilder.h"

#include <QDebug>

#include <QtMath>

MeshPackGeometryCreator::MeshPackGeometryCreator(std::vector<std::pair<QRgb, int> > &colors,
                                                 std::shared_ptr<IMeshPattern> pattern,
                                                 int patternsCount, int batchSize)
    : m_pattern(std::make_shared<Icosahedron>())//pattern)
    , m_meshesForCreatingBuffer()
    , m_resultMeshes()
    , m_meshBuilder(new MeshBuilder(m_pattern,batchSize))
    , m_lastPatternIndex(patternsCount-1)
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
*   Called from main thread and current OpenGL context
*   for creating vertex buffers for new meshes
******************************************************************************/
void MeshPackGeometryCreator::createMeshBuffersIfNeed()
{
    while (!m_meshesForCreatingBuffer.empty()) {
        m_bufferStackMutex.lock();
        std::shared_ptr<Mesh> topMesh = m_meshesForCreatingBuffer.top();
        m_meshesForCreatingBuffer.pop();
        m_bufferStackMutex.unlock();

        topMesh->createBuffer();
        //m_result->addMesh(topMesh);

    }
}


/******************************************************************************
*   Adds a geometry part to the mesh result
******************************************************************************/
void MeshPackGeometryCreator::addPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    bool builderFilled = m_meshBuilder->addMeshByPattern(modelMatrix,color) || m_currentPatternIndex == m_lastPatternIndex;
    if (builderFilled)
        addNewMeshBatch();

    m_currentPatternIndex++;
}

/******************************************************************************
*   Adds a mesh to the result
******************************************************************************/
void MeshPackGeometryCreator::addNewMeshBatch()
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
*   Starts new mesh
******************************************************************************/
void MeshPackGeometryCreator::startNewBatch()
{
    m_batchMesh = std::make_shared<Mesh>(nullptr, m_drawMode);
    m_meshBuilder.reset(new MeshBuilder(m_pattern,m_meshBuilderSize));
}


std::list<std::shared_ptr<Mesh> > MeshPackGeometryCreator::resultMeshes() const
{
    std::lock_guard<std::mutex> lock(m_resultMutex);
    return m_resultMeshes;
}

bool MeshPackGeometryCreator::isCreatingFininshed() const
{
    return m_isCreatingFinished.load();
}

void MeshPackGeometryCreator::startCreation()
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





MeshPackBuilder::MeshPackBuilder(const std::unordered_map<QRgb, int> &colors, std::shared_ptr<IMeshPattern> pattern,
                                 std::shared_ptr<QOpenGLShaderProgram> shader,
                                 GLenum drawMode, int patternsCount, int batchSize)
    : m_pattern(pattern)
    //, m_lastPatternIndex(patternsCount-1)
    , m_result(std::make_shared<MeshPack>())
    , m_shader(shader)
    , m_patternsCount(patternsCount)
    , m_batchSize(batchSize)
    //, m_drawMode(drawMode)
    //, m_batchMesh(std::make_shared<Mesh>(shader,drawMode))
    //, m_meshBuilder(new MeshBuilder(m_pattern,batchSize))//m_pattern->patternDataSize()*batchSize))
   // , m_currentPatternIndex(0)
    //, m_meshBuilderSize(batchSize)//pattern->patternDataSize()*batchSize)
   // , m_meshesForCreatingBuffer()
    , m_imageColorsBatches()
    , m_coresCount(1)//std::thread::hardware_concurrency())
    , m_threads()
    //, m_mutex()
    //, m_threadsFinished()
    , m_geometryCreators()
{
    m_timer.start();
    //m_threadsFinished.store(0);

    if (m_coresCount == 0)
        m_coresCount++;

    int colorsBatchSize = colors.size() / m_coresCount + 1;

    m_imageColorsBatches.resize(m_coresCount);
    m_geometryCreators.resize(m_coresCount);
    m_threads.reserve(m_coresCount);

    for (int i = 0; i < m_coresCount; ++i)
        m_imageColorsBatches[i].reserve(colorsBatchSize);

    int currentCore = 0;
    for (auto it = colors.cbegin(); it != colors.cend(); ++it) {
        if (m_imageColorsBatches[currentCore].size() == colorsBatchSize)
            currentCore++;
        m_imageColorsBatches[currentCore].emplace_back(it->first,it->second);
    }
    qDebug() << "coping finished=============================================";
}

MeshPackBuilder::~MeshPackBuilder()
{
    for (auto & t : m_threads) {
        if(t.joinable())
            t.join();
    }

    qDebug() << "in destructor for builder: isBuild" << isGeometryBuilt();
}


/******************************************************************************
*   Adds a geometry part to the mesh result
******************************************************************************/
/*void MeshPackBuilder::addPattern(const QMatrix4x4 &modelMatrix, QRgb color)
{
    bool builderFilled = m_meshBuilder->addMeshByPattern(modelMatrix,color) || m_currentPatternIndex == m_lastPatternIndex;
    if (builderFilled)
        addNewMeshBatch();

    m_currentPatternIndex++;
}*/


/******************************************************************************
*   Returns result
******************************************************************************/
std::shared_ptr<MeshPack> MeshPackBuilder::result() const
{
    for (int i = 0; i < m_coresCount; ++i) {
        std::list<std::shared_ptr<Mesh>> result = m_geometryCreators[i]->resultMeshes();
        for (auto & mesh : result) {
            m_result->addMesh(mesh);
        }
    }
    m_result->setShader(m_shader);
    qDebug() << m_result->meshesCount() << m_timer.elapsed();
    return m_result;
}

void MeshPackBuilder::createMeshGeometry()
{
    for (int i = 0; i < m_coresCount; ++i) {
        m_geometryCreators[i].reset(new MeshPackGeometryCreator(m_imageColorsBatches[i],m_pattern,m_patternsCount,m_batchSize));
        std::thread t([=]{
            //createMeshGeometry(m_imageColorsBatches[i]);
            m_geometryCreators[i]->startCreation();
        });
        m_threads.push_back(std::move(t));
    }

    m_imageColorsBatches.clear();
    m_imageColorsBatches.shrink_to_fit();
}

/*void MeshPackBuilder::createMeshGeometry(const std::vector<std::pair<QRgb, int> > &colors)
{
    for (auto it = colors.cbegin(); it != colors.cend(); ++it) {
        QColor clrHsv = QColor(it->first).toHsv();

        QMatrix4x4 model;
        model.rotate(clrHsv.hsvHue(),UP);
        model.translate(clrHsv.saturationF(),clrHsv.valueF(),0.0f);
        model.scale(qPow(it->second,VOLUME_POWER) * DIAGRAM_POINT_SCALE_FACTOR);

        addPattern(model,it->first);
    }
    m_threadsFinished.store(m_threadsFinished.load() + 1);
    qDebug() << "ALL CALCULUS DONE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}*/

void MeshPackBuilder::createMeshBuffersIfNeed()
{
    for (int i = 0; i < m_coresCount; ++i) {
        m_geometryCreators[i]->createMeshBuffersIfNeed();
    }
}

bool MeshPackBuilder::isGeometryBuilt()
{
    int creatorsFinished = 0;
    for (int i = 0; i < m_coresCount; ++i) {
        if (m_geometryCreators[i]->isCreatingFininshed())
            ++creatorsFinished;
    }

    return creatorsFinished == m_coresCount;
}


/******************************************************************************
*   Adds a mesh to the result
******************************************************************************/
/*void MeshPackBuilder::addNewMeshBatch()
{
    m_batchMesh->setVertices(m_meshBuilder->resultVertices());
    m_batchMesh->setNormals(m_meshBuilder->resultNormals());
    m_batchMesh->setColors(m_meshBuilder->resultColors());

    //m_batchMesh->createBuffer();

    //m_result->addMesh(m_batchMesh);
    m_mutex.lock();
    m_meshesForCreatingBuffer.push(m_batchMesh);
    m_mutex.unlock();

    startNewBatch();
}*/


/******************************************************************************
*   Starts new mesh
******************************************************************************/
/*void MeshPackBuilder::startNewBatch()
{
    m_batchMesh = std::make_shared<Mesh>(m_shader, m_drawMode);
    m_meshBuilder.reset(new MeshBuilder(m_pattern,m_meshBuilderSize));
}*/

