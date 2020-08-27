#include "colordiagramcontroller.h"

ColorDiagramController::ColorDiagramController(ColorSplitterModel &model)
    : m_model(model)
    , m_timer()
{
    connect(&m_timer,&QTimer::timeout,[=](){
        if (checkUpdateDiagram()) {
            m_timer.stop();
            emit diagramChanged();
        }
    });
}

/******************************************************************************
*   Fills diagram from model data
******************************************************************************/
void ColorDiagramController::fillDiagram()
{
    m_scene.lock()->refillDiagram(m_model.decomposedColors());
    m_timer.start(20);
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
        m_timer.start(20);
    }
}


/******************************************************************************
*   Binds color diagram scene to the controller
******************************************************************************/
void ColorDiagramController::bindScene(std::shared_ptr<ColorDiagramScene> scene)
{
    m_scene = scene;
}

bool ColorDiagramController::checkUpdateDiagram()
{
    bool needToUpdate = false;
    if (!m_scene.expired()) {
        m_scene.lock()->updateDiagram();
        needToUpdate = m_scene.lock()->isNewDiagramBuilt();
        if (needToUpdate) {
            m_scene.lock()->showNewDiagram();
        }
    }
    return needToUpdate;
}
