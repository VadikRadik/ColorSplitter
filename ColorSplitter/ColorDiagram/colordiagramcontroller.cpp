#include "colordiagramcontroller.h"

ColorDiagramController::ColorDiagramController(ColorSplitterModel &model)
    : m_model(model)
{

}

void ColorDiagramController::fillDiagram()
{
    m_scene.lock()->refillDiagram(m_model.decomposedColors());
}

void ColorDiagramController::bindScene(std::shared_ptr<ColorDiagramScene> scene)
{
    m_scene = scene;
}
