#include "meshpackbuilder.h"

MeshPackBuilder::MeshPackBuilder(const std::unordered_map<QRgb, int> &colors, std::shared_ptr<IMeshPattern> pattern,
                                 std::shared_ptr<QOpenGLShaderProgram> shader,
                                 int batchSize)
    : m_pattern(pattern)
    , m_result(std::make_shared<MeshPack>())
    , m_shader(shader)
    , m_batchSize(batchSize)
    , m_imageColorsBatches()
    , m_threadsCount(std::thread::hardware_concurrency())
    , m_threads()
    , m_geometryCreators()
{
    if (m_threadsCount == 0)
        m_threadsCount++;

    int colorsBatchSize = colors.size() / m_threadsCount + 1;

    m_imageColorsBatches.resize(m_threadsCount);
    m_geometryCreators.resize(m_threadsCount);
    m_threads.reserve(m_threadsCount);

    for (int i = 0; i < m_threadsCount; ++i)
        m_imageColorsBatches[i].reserve(colorsBatchSize);

    int currentThread = 0;
    for (auto it = colors.cbegin(); it != colors.cend(); ++it) {
        if (m_imageColorsBatches[currentThread].size() == colorsBatchSize)
            currentThread++;
        m_imageColorsBatches[currentThread].emplace_back(it->first,it->second);
    }
}

MeshPackBuilder::~MeshPackBuilder()
{
    for (auto & t : m_threads) {
        if(t.joinable())
            t.join();
    }
}


/******************************************************************************
*   Returns the result
******************************************************************************/
std::shared_ptr<MeshPack> MeshPackBuilder::packResult()
{
    createMeshBuffersIfNeed();
    for (int i = 0; i < m_threadsCount; ++i) {
        std::list<std::shared_ptr<Mesh>> result = m_geometryCreators[i]->resultMeshes();
        for (auto & mesh : result) {
            m_result->addMesh(mesh);
        }
    }
    m_result->setShader(m_shader);

    return m_result;
}


/******************************************************************************
*   Starts a diagram creation with several threads
******************************************************************************/
void MeshPackBuilder::createMeshGeometry()
{
    for (int i = 0; i < m_threadsCount; ++i) {
        m_geometryCreators[i].reset(new DiagramGeometryCreator(m_imageColorsBatches[i],m_pattern,m_batchSize));
        std::thread t([=]{
            m_geometryCreators[i]->startCreation();
        });
        m_threads.push_back(std::move(t));
    }

    m_imageColorsBatches.clear();
}


/******************************************************************************
*   Checks for new meshes for creating vertex buffers.
*   Must be called from the main thread and with a correct OpenGL context
******************************************************************************/
void MeshPackBuilder::createMeshBuffersIfNeed()
{
    for (int i = 0; i < m_threadsCount; ++i) {
        m_geometryCreators[i]->createMeshBuffersIfNeed();
    }
}


/******************************************************************************
*   Checks for finish creating
*   Must be called from the main thread and with a correct OpenGL context
******************************************************************************/
bool MeshPackBuilder::isGeometryBuilt()
{
    int creatorsFinished = 0;
    for (int i = 0; i < m_threadsCount; ++i) {
        if (m_geometryCreators[i]->isCreatingFininshed())
            ++creatorsFinished;
    }

    return creatorsFinished == m_threadsCount;
}
