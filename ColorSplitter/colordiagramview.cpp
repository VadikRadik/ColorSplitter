#include "colordiagramview.h"
#include "OpenGLWidget/scenebuilder.h"
#include "OpenGLWidget/centred3deulercamera.h"
#include "OpenGLWidget/ortho2dcamera.h"
#include "DrawableObjects/rasterimage.h"

/******************************************************************************
*   Конструктор
******************************************************************************/
ColorDiagramView::ColorDiagramView()
    : m_imegeWidget(nullptr)
{
    SceneBuilder builder;
    builder.setCamera(new Centred3DEulerCamera());
    //builder.setCamera(new Ortho2DCamera());
    std::shared_ptr<Scene> scene = builder.build();

    m_imegeWidget = new OpenGLWidget(scene);
    m_scene = scene;

}


/******************************************************************************
*   Создание и/или передача виджета представления
******************************************************************************/
QWidget *ColorDiagramView::createWidget() const
{
    return m_imegeWidget;
}


/******************************************************************************
*   Обновление представления по событию изменения модели
******************************************************************************/
void ColorDiagramView::update(SplitterViewModel *model)
{
    m_scene.lock()->addObject(std::make_shared<RasterImage>(QImage("f:/tempos/снимок002.png")));
}
