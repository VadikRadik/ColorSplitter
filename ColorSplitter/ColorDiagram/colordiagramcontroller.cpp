#include "colordiagramcontroller.h"

ColorDiagramController::ColorDiagramController(ColorSplitterModel &model)
    : m_model(model)
{

}

/******************************************************************************
*   Fills diagram from model data
******************************************************************************/
void ColorDiagramController::fillDiagram()
{
    m_scene.lock()->refillDiagram(m_model.decomposedColors());
}


/******************************************************************************
*   Switches the light source for the diagram scene
******************************************************************************/
void ColorDiagramController::switchLight(bool light)
{
    m_scene.lock()->setLight(light);
}


/******************************************************************************
*   Switches shape for the diagram points
******************************************************************************/
void ColorDiagramController::setShape(EDiagramDotShape shape)
{
    if (!m_scene.expired()) {
        m_scene.lock()->setShape(shape);
        m_scene.lock()->refillDiagram(m_model.decomposedColors());
    }
}


/******************************************************************************
*   Binds color diagram scene to the controller
******************************************************************************/
void ColorDiagramController::bindScene(std::shared_ptr<ColorDiagramScene> scene)
{
    m_scene = scene;
}
