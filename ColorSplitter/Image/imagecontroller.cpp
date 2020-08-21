#include "imagecontroller.h"

ImageController::ImageController(ColorSplitterModel &model)
    : m_model(model)
{

}


/******************************************************************************
*   Binds the scene to the controller
******************************************************************************/
void ImageController::bindScene(std::shared_ptr<ImageScene> scene)
{
    m_scene = scene;
}


/******************************************************************************
*   The user's input handlers
******************************************************************************/

void ImageController::wheelEvent(QWheelEvent *event)
{
    // do nothing
}

void ImageController::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
        if (!m_scene.expired())
            m_scene.lock()->expandFrame(event->pos());
    }
}

void ImageController::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
        if (!m_scene.expired())
            m_scene.lock()->createFrame(event->pos());
    }
}

void ImageController::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        m_model.setCutFrame(m_scene.lock()->getFrameRect());
}

void ImageController::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        m_model.setCutFrame(QRect());
}

void ImageController::keyReleaseEvent(QKeyEvent *event)
{
    // do nothing
}
