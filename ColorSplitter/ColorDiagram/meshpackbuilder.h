#ifndef MESHPACKBUILDER_H
#define MESHPACKBUILDER_H

#include "ColorDiagram/meshbuilder.h"
#include "DrawableObjects/meshpack.h"
#include "DrawableObjects/mesh.h"
#include "diagramgeometrycreator.h"

#include <unordered_map>
#include <thread>


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
                    std::shared_ptr<QOpenGLShaderProgram> shader, int batchSize = 2500000);
    ~MeshPackBuilder();

    std::shared_ptr<MeshPack> packResult();

    void createMeshGeometry();
    void createMeshBuffersIfNeed();
    bool isGeometryBuilt();

private:
    std::shared_ptr<IMeshPattern> m_pattern;
    std::shared_ptr<MeshPack> m_result;
    std::shared_ptr<QOpenGLShaderProgram> m_shader;

    int m_batchSize;
    int m_threadsCount;

    std::vector<std::vector<std::pair<QRgb,int>>> m_imageColorsBatches;
    std::vector<std::thread> m_threads;
    std::vector<std::unique_ptr<DiagramGeometryCreator>> m_geometryCreators;
};

#endif // MESHPACKBUILDER_H
