#include "imageview.h"
#include "OpenGLWidget/ortho2dcamera.h"

/******************************************************************************
*   Конструктор
******************************************************************************/
ImageView::ImageView()
    : m_imegeWidget(nullptr)
{
    std::shared_ptr<ImageScene> scene = std::make_shared<ImageScene>(new Ortho2DCamera());

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
