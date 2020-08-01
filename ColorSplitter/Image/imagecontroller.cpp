#include "imagecontroller.h"

ImageController::ImageController(ColorSplitterModel &model)
    : m_model(model)
{

}

void ImageController::bindScene(std::shared_ptr<ImageScene> scene)
{
    m_scene = scene;
}

void ImageController::wheelEvent(QWheelEvent *event)
{

}

void ImageController::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        m_scene.lock()->expandFrame(event->pos());
}

void ImageController::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        m_scene.lock()->createFrame(event->pos());
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

}
