#include "colordiagramcontroller.h"

#include <QTime>
#include <QDebug>

ColorDiagramController::ColorDiagramController(ColorSplitterModel &model)
    : m_model(model)
{

}

void ColorDiagramController::fillDiagram()
{
    QTime timer;
    timer.start();
    m_scene.lock()->refillDiagram(m_model.decomposedColors());
    qDebug() << "test time: " << timer.elapsed();
}

void ColorDiagramController::bindScene(std::shared_ptr<ColorDiagramScene> scene)
{
    m_scene = scene;
}
