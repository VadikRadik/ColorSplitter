#ifndef DIAGRAMGEOMETRYCREATOR_H
#define DIAGRAMGEOMETRYCREATOR_H

#include <mutex>
#include <atomic>
#include <stack>

#include "DrawableObjects/mesh.h"
#include "imeshpattern.h"
#include "meshbuilder.h"

/******************************************************************************
*
*   Thread safety diagram mesh builder
*
******************************************************************************/
class DiagramGeometryCreator
{
public:
    DiagramGeometryCreator(std::vector<std::pair<QRgb,int>> & colors,
                            std::shared_ptr<IMeshPattern> pattern, int batchSize);
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

#endif // DIAGRAMGEOMETRYCREATOR_H
