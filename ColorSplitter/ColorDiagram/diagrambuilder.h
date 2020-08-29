#ifndef DIAGRAMBUILDER_H
#define DIAGRAMBUILDER_H

#include "ColorDiagram/meshbuilder.h"
#include "DrawableObjects/meshpack.h"
#include "DrawableObjects/mesh.h"
#include "diagramgeometrycreator.h"
#include "icolordiagramobserver.h"

#include <unordered_map>
#include <thread>

#include <QTimer>


/******************************************************************************
*
*   Creates wrappers for several meshes
*
******************************************************************************/
class DiagramBuilder
{
public:
    DiagramBuilder(const std::unordered_map<QRgb, int> &colors,
                    std::shared_ptr<IMeshPattern> pattern,
                    std::shared_ptr<QOpenGLShaderProgram> shader, int batchSize = 2500000);
    ~DiagramBuilder();

    std::shared_ptr<MeshPack> packResult();

    void createMeshGeometry();
    void createMeshBuffersIfNeed();
    bool isGeometryBuilt();
    void subscribe(IObserver * subscriber);

private:
    std::shared_ptr<IMeshPattern> m_pattern;
    std::shared_ptr<MeshPack> m_result;
    std::shared_ptr<QOpenGLShaderProgram> m_shader;

    int m_batchSize;
    int m_threadsCount;

    std::vector<std::vector<std::pair<QRgb,int>>> m_imageColorsBatches;
    std::vector<std::thread> m_threads;
    std::vector<std::unique_ptr<DiagramGeometryCreator>> m_geometryCreators;

    IObserver * m_creatingSubscriber;

    QTimer m_timer;
    static const int TIMER_PERIOD = 50;
};

#endif // DIAGRAMBUILDER_H
