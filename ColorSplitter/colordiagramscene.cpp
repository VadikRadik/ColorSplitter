#include "colordiagramscene.h"
#include "DrawableObjects/background.h"
#include "DrawableObjects/rasterimage.h"
#include "meshbuilder.h"

#include <QTime>

ColorDiagramScene::ColorDiagramScene(ICamera * camera)
    : AbstractScene(camera)
    , m_colorScalePattern(std::make_shared<ScalePartPattern>())
    , m_directLightedMeshShader(nullptr)
{

}

void ColorDiagramScene::createColorScale()
{
    std::shared_ptr<Mesh> colorScale = std::make_shared<Mesh>(m_directLightedMeshShader, GL_QUADS);
    m_scale = colorScale;

    MeshBuilder meshBuilder(m_colorScalePattern,m_colorScalePattern->patternDataSize()*COLOR_SCALE_PARTS_COUNT);

    for (int i = 0; i < COLOR_SCALE_PARTS_COUNT; ++i) {
        QMatrix4x4 model;
        model.rotate(i,UP);
        model.translate(0.0f,1.0f,0.0f);

        QColor clrHsv;
        clrHsv.setHsv(i,255,255);

        meshBuilder.addMeshByPattern(model,clrHsv);
    }

    m_scale.lock()->setVertices(meshBuilder.resultVertices());
    m_scale.lock()->setNormals(meshBuilder.resultNormals());
    m_scale.lock()->setColors(meshBuilder.resultColors());

    m_scale.lock()->createBuffer();
    GLenum errorCode = m_openGLContext->functions()->glGetError();
    if (errorCode != 0)
        qWarning() << "OpenGL error code:" << errorCode;

    addObject(colorScale);
}

void ColorDiagramScene::createTestMesh()
{
    std::shared_ptr<MeshPack> diagramMesh = std::make_shared<MeshPack>();
    m_diagramMesh = diagramMesh;

    int patternsCount = 50000;//27.4 Mb
    std::unique_ptr<MeshBuilder> meshBuilder(new MeshBuilder(m_colorScalePattern,m_colorScalePattern->patternDataSize()*patternsCount));

    std::shared_ptr<Mesh> meshBatch = std::make_shared<Mesh>(m_directLightedMeshShader, GL_QUADS);
    int i = 0;
    for (int j = 0; j < 1550000; ++j) {

        QMatrix4x4 model;
        model.rotate(j,UP);
        model.translate(0.0f,0.05f*i+1.1f,0.000005f*j);

        QColor clrHsv;
        clrHsv.setHsv(j % 255,255,255);

        bool builderFilled = meshBuilder->addMeshByPattern(model,clrHsv);
        if (builderFilled) {

            meshBatch->setVertices(meshBuilder->resultVertices());
            meshBatch->setNormals(meshBuilder->resultNormals());
            meshBatch->setColors(meshBuilder->resultColors());

            meshBatch->createBuffer();
            GLenum errorCode = m_openGLContext->functions()->glGetError();
            if (errorCode != 0)
                qWarning() << "OpenGL error code:" << errorCode;

            m_diagramMesh.lock()->addMesh(meshBatch);

            meshBatch = std::make_shared<Mesh>(m_directLightedMeshShader, GL_QUADS);
            meshBuilder.reset(new MeshBuilder(m_colorScalePattern,m_colorScalePattern->patternDataSize()*patternsCount));
            ++i;
        }

    }
    addObject(diagramMesh);
}

void ColorDiagramScene::initialize()
{
    addObject(std::make_shared<Background>(SCENE_BACKGROUND_COLOR));

    m_directLightedMeshShader = createShader(":/shaders/direct_ligted_mesh.vsh",":/shaders/direct_ligted_mesh.fsh", QString());

    createColorScale();
    createTestMesh();
}
