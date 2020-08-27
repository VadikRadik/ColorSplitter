#ifndef MESHPACKBUILDER_H
#define MESHPACKBUILDER_H

#include "ColorDiagram/meshbuilder.h"
#include "DrawableObjects/meshpack.h"
#include "DrawableObjects/mesh.h"

#include <stack>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <atomic>

#include <QTime>


class MeshPackGeometryCreator
{
public:
    MeshPackGeometryCreator(std::vector<std::pair<QRgb,int>> & colors,
                            std::shared_ptr<IMeshPattern> pattern,
                            int patternsCount, int batchSize);
    void createMeshBuffersIfNeed();

    std::list<std::shared_ptr<Mesh>> resultMeshes() const;
    bool isCreatingFininshed() const;
    void startCreation();

private:
    void addPattern(const QMatrix4x4 & modelMatrix, QRgb color);
    void addNewMeshBatch();
    void startNewBatch();

private:
    std::shared_ptr<IMeshPattern> m_pattern;
    std::stack<std::shared_ptr<Mesh>> m_meshesForCreatingBuffer;
    std::list<std::shared_ptr<Mesh>> m_resultMeshes;
    std::unique_ptr<MeshBuilder> m_meshBuilder;
    std::mutex m_bufferStackMutex;
    mutable std::mutex m_resultMutex;
    int m_currentPatternIndex;
    int m_lastPatternIndex;
    GLenum m_drawMode;
    int m_meshBuilderSize;
    std::shared_ptr<Mesh> m_batchMesh;
    std::atomic<bool> m_isCreatingFinished;
    std::vector<std::pair<QRgb, int> > m_colors;

    const float VOLUME_POWER = 0.27f;
    const float DIAGRAM_POINT_SCALE_FACTOR = 0.007f;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
};


/******************************************************************************
*
*   Creates wrappers for several meshes
*
******************************************************************************/
class MeshPackBuilder
{
public:
    MeshPackBuilder(const std::unordered_map<QRgb, int> &colors,
                    std::shared_ptr<IMeshPattern> pattern,
                    std::shared_ptr<QOpenGLShaderProgram> shader,
                    GLenum drawMode, int patternsCount, int batchSize = 500000);
    ~MeshPackBuilder();


    void addPattern(const QMatrix4x4 & modelMatrix, QRgb color);

    std::shared_ptr<MeshPack> result() const;

    void createMeshGeometry();
    void createMeshBuffersIfNeed();
    bool isGeometryBuilt();

//private:
//    void addNewMeshBatch();
//    void startNewBatch();
//    void createMeshGeometry(const std::vector<std::pair<QRgb,int>> & colors);

private:
    std::shared_ptr<IMeshPattern> m_pattern;

    std::shared_ptr<MeshPack> m_result;
    std::shared_ptr<QOpenGLShaderProgram> m_shader;



    int m_patternsCount;
    int m_batchSize;


    int m_coresCount;
    //std::atomic<int> m_threadsFinished;


    std::vector<std::vector<std::pair<QRgb,int>>> m_imageColorsBatches;

    std::vector<std::thread> m_threads;
    std::vector<std::unique_ptr<MeshPackGeometryCreator>> m_geometryCreators;
    //std::mutex m_mutex;

    QTime m_timer;


};

#endif // MESHPACKBUILDER_H
