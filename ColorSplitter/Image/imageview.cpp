#include "imageview.h"
#include "OpenGLWidget/ortho2dcamera.h"
#include "colorsplittermodel.h"

/******************************************************************************
*   Constructor
******************************************************************************/
ImageView::ImageView(std::shared_ptr<ImageController> controller)
    : m_imegeWidget(nullptr)
{
    std::shared_ptr<ImageScene> scene = std::make_shared<ImageScene>(new Ortho2DCamera());

    controller->bindScene(scene);
    m_imegeWidget = new OpenGLWidget(scene, controller);
    m_scene = scene;
}


/******************************************************************************
*   Returns the view widget
******************************************************************************/
QWidget *ImageView::createWidget() const
{
    return m_imegeWidget;
}


/******************************************************************************
*   Updates the view by changing of a model state
******************************************************************************/
void ImageView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{
    switch (stateChange) {
    case EModelUpdates::IMAGE_CHANGED:
        m_scene.lock()->changeImage(model->image());
        m_imegeWidget->update();
        break;
    case EModelUpdates::CUT_FRAME_CHANGED:
        if (model->cutFrame().isNull()) {
            m_scene.lock()->removeFrame();
            m_imegeWidget->update();
        }
        break;
    default:
        break;
    }
}
