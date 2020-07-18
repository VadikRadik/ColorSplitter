#include "imageview.h"
#include "OpenGLWidget/scenebuilder.h"
#include "OpenGLWidget/ortho2dcamera.h"

/******************************************************************************
*   Конструктор
******************************************************************************/
ImageView::ImageView()
    : m_imegeWidget(nullptr)
{
    SceneBuilder builder;
    builder.setCamera(new Ortho2DCamera());
    std::shared_ptr<Scene> scene = builder.build();

    m_imegeWidget = new OpenGLWidget(scene);
    m_scene = scene;
}


/******************************************************************************
*   Создание и/или передача виджета представления
******************************************************************************/
QWidget *ImageView::createWidget() const
{
    return m_imegeWidget;
}


/******************************************************************************
*   Обновление представления по событию изменения модели
******************************************************************************/
void ImageView::update(SplitterViewModel *model)
{

}
