#include "imageview.h"
#include "OpenGLWidget/ortho2dcamera.h"
#include "colorsplittermodel.h"

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
void ImageView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{
    switch (stateChange) {
    case EModelUpdates::IMAGE_CHANGED:
        m_scene.lock()->changeImage(model->image());
        m_imegeWidget->update();
        break;
    default:
        break;
    }
}
