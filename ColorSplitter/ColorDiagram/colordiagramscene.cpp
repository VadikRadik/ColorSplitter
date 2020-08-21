#include "colordiagramscene.h"
#include "DrawableObjects/background.h"
#include "DrawableObjects/rasterimage.h"
#include "meshbuilder.h"
#include "meshpackbuilder.h"

#include <QtMath>

/******************************************************************************
*   Constructor
******************************************************************************/
ColorDiagramScene::ColorDiagramScene(ICamera * camera)
    : AbstractScene(camera)
    , m_directLightedMeshShader(nullptr)
    , m_noLightedMeshShader(nullptr)
    , m_currentMeshShader(nullptr)
    , m_colorScalePattern(std::make_shared<ScalePartPattern>())
    , m_tetrahedronPattern(std::make_shared<TetrahedronPattern>())
    , m_cubePattern(std::make_shared<CubePattern>())
    , m_octahedronPattern(std::make_shared<OctahedronPattern>())
    , m_icosahedronPattern(std::make_shared<Icosahedron>())
    , m_currentPattern(m_cubePattern)
    , m_isLight(true)
{

}

/******************************************************************************
*   Creates the color scale
******************************************************************************/
void ColorDiagramScene::createColorScale()
{
    std::shared_ptr<Mesh> colorScale = std::make_shared<Mesh>(m_directLightedMeshShader, m_colorScalePattern->drawMode());
    m_scale = colorScale;

    MeshBuilder meshBuilder(m_colorScalePattern,m_colorScalePattern->patternDataSize()*COLOR_SCALE_PARTS_COUNT);

    for (int i = 0; i < COLOR_SCALE_PARTS_COUNT; ++i) {
        QMatrix4x4 model;
        model.rotate(i,UP);
        model.translate(0.0f,1.0f,0.0f);

        QColor clrHsv;
        clrHsv.setHsv(i,255,255);

        meshBuilder.addMeshByPattern(model,clrHsv.rgb());
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


/******************************************************************************
*   Switches the light source for the diagram scene
******************************************************************************/
void ColorDiagramScene::setLight(bool light)
{
    m_isLight = light;
    m_currentMeshShader = m_isLight ? m_directLightedMeshShader : m_noLightedMeshShader;
    if (!m_diagramMesh.expired())
        m_diagramMesh.lock()->setShader(m_currentMeshShader);
}


/******************************************************************************
*   Switches shape for the diagram points
******************************************************************************/
void ColorDiagramScene::setShape(EDiagramDotShape shape)
{
    switch (shape) {
    case EDiagramDotShape::TETRAHEDRON:
        m_currentPattern = m_tetrahedronPattern;
        break;
    case EDiagramDotShape::CUBE:
        m_currentPattern = m_cubePattern;
        break;
    case EDiagramDotShape::OCTAHEDRON:
        m_currentPattern = m_octahedronPattern;
        break;
    case EDiagramDotShape::ICOSAHEDRON:
        m_currentPattern = m_icosahedronPattern;
        break;
    default:
        break;
    }
}


/******************************************************************************
*   Creates shaders and diagram objects
******************************************************************************/
void ColorDiagramScene::initialize()
{
    addObject(std::make_shared<Background>(SCENE_BACKGROUND_COLOR));

    m_directLightedMeshShader = createShader(":/shaders/direct_lighted_mesh.vsh",":/shaders/direct_lighted_mesh.fsh", QString());
    m_noLightedMeshShader = createShader(":/shaders/no_lighted_mesh.vsh",":/shaders/no_lighted_mesh.fsh", QString());
    setLight(m_isLight);

    createColorScale();
}


/******************************************************************************
*   Creates the diagram mesh
******************************************************************************/
void ColorDiagramScene::refillDiagram(const std::unordered_map<QRgb, int> &colors)
{
    makeCurrentContext();

    if (!m_diagramMesh.expired())
        removeObject(m_diagramMesh.lock());

    MeshPackBuilder diagramBuilder(m_currentPattern,m_currentMeshShader,m_currentPattern->drawMode(),colors.size());

    for (auto it = colors.cbegin(); it != colors.cend(); ++it) {
        QColor clrHsv = QColor(it->first).toHsv();

        QMatrix4x4 model;
        model.rotate(clrHsv.hsvHue(),UP);
        model.translate(clrHsv.saturationF(),clrHsv.valueF(),0.0f);
        model.scale(qPow(it->second,VOLUME_POWER) * DIAGRAM_POINT_SCALE_FACTOR);

        diagramBuilder.addPattern(model,it->first);
    }

    GLenum errorCode = m_openGLContext->functions()->glGetError();
    if (errorCode != 0)
        qWarning() << "OpenGL error code:" << errorCode;

    m_diagramMesh = diagramBuilder.result();
    addObject(m_diagramMesh.lock());
}
