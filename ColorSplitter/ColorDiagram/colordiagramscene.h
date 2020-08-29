#ifndef COLORDIAGRAMSCENE_H
#define COLORDIAGRAMSCENE_H

#include <unordered_map>

#include "OpenGLWidget/abstractscene.h"
#include "DrawableObjects/mesh.h"
#include "DrawableObjects/meshpack.h"
#include "imeshpattern.h"
#include "diagrambuilder.h"
#include "iwidgetsupdatable.h"

#include <QColor>

enum EDiagramDotShape
{
    TETRAHEDRON,
    CUBE,
    OCTAHEDRON,
    ICOSAHEDRON
};


/******************************************************************************
*
*   Scene for the color diagram
*
******************************************************************************/
class ColorDiagramScene : public AbstractScene
                        , public IObserver
{
public:
    ColorDiagramScene(ICamera *camera);

    virtual void initialize() override;

    void refillDiagram(const std::unordered_map<QRgb, int> & colors);
    void flushDiagram();

    void setLight(bool light);
    void setShape(EDiagramDotShape shape);

    void subscribeView(IWidgetsUpdatable * view);
    virtual void update(EColorDiagramState state) override;

private:
    void createColorScale();
    void updateDiagram();
    void showNewDiagram();

private:
    std::shared_ptr<QOpenGLShaderProgram> m_directLightedMeshShader;
    std::shared_ptr<QOpenGLShaderProgram> m_noLightedMeshShader;
    std::shared_ptr<QOpenGLShaderProgram> m_currentMeshShader;

    std::weak_ptr<Mesh> m_scale;
    std::weak_ptr<MeshPack> m_diagramMesh;

    std::shared_ptr<IMeshPattern> m_colorScalePattern;
    std::shared_ptr<IMeshPattern> m_tetrahedronPattern;
    std::shared_ptr<IMeshPattern> m_cubePattern;
    std::shared_ptr<IMeshPattern> m_octahedronPattern;
    std::shared_ptr<IMeshPattern> m_icosahedronPattern;
    std::shared_ptr<IMeshPattern> m_currentPattern;

    std::unique_ptr<DiagramBuilder> m_diagramBuilder;
    IWidgetsUpdatable * m_view;

    bool m_isLight;

    const QColor SCENE_BACKGROUND_COLOR = QColor::fromRgbF(0.5f,0.5f,0.5f);
    const int COLOR_SCALE_PARTS_COUNT = 360;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
    const float VOLUME_POWER = 0.27f;
    const float DIAGRAM_POINT_SCALE_FACTOR = 0.007f;
};

#endif // COLORDIAGRAMSCENE_H
