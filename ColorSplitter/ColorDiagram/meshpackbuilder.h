#ifndef MESHPACKBUILDER_H
#define MESHPACKBUILDER_H

#include "ColorDiagram/meshbuilder.h"
#include "DrawableObjects/meshpack.h"
#include "DrawableObjects/mesh.h"

class MeshPackBuilder
{
public:
    MeshPackBuilder(std::shared_ptr<IMeshPattern> pattern, std::shared_ptr<QOpenGLShaderProgram> shader, GLenum drawMode, int patternsCount, int batchSize = 50000);

    void addPattern(const QMatrix4x4 & modelMatrix, const QColor & color);

    std::shared_ptr<MeshPack> result() const;

private:
    void addNewMeshBatch();
    void startNewBatch();

private:
    std::shared_ptr<IMeshPattern> m_pattern;
    int m_lastPattern;
    std::shared_ptr<MeshPack> m_result;
    std::shared_ptr<QOpenGLShaderProgram> m_shader;
    GLenum m_drawMode;
    std::shared_ptr<Mesh> m_batchMesh;
    std::unique_ptr<MeshBuilder> m_meshBuilder;
    int m_currentPatternIndex;
    int m_meshBuilderSize;
};

#endif // MESHPACKBUILDER_H
