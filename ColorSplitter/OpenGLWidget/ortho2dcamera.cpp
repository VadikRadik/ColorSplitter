#include "ortho2dcamera.h"

/******************************************************************************
*   Обработка изменения вьюпорта
******************************************************************************/
void Ortho2DCamera::resizeView(int width, int height)
{
    m_viewRect.setSize(QSizeF(width,height));
}


/******************************************************************************
*   Возврат матрицы проекции
******************************************************************************/
QMatrix4x4 Ortho2DCamera::projectionMatrix() const
{
    QMatrix4x4 projection;
    projection.ortho(m_viewportTransformMatrix.mapRect(m_viewRect));
    return projection;
}


/******************************************************************************
*   Возврат матрицы вью
******************************************************************************/
QMatrix4x4 Ortho2DCamera::viewMatrix() const
{
    return QMatrix4x4();
}


/******************************************************************************
*   Вектор направления камеры
******************************************************************************/
QVector3D Ortho2DCamera::viewDirection() const
{
    return VIEW_DIRECTION;
}


/******************************************************************************
*   Перевести координаты виджета в координаты видимого пространства камеры
******************************************************************************/
QVector3D Ortho2DCamera::projectPoint(QPoint point) const
{
    return QVector3D(m_viewportTransformMatrix.map(point));
}


/******************************************************************************
*   Приближение/удаление камеры
******************************************************************************/
void Ortho2DCamera::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().isNull())
        return;

    float zoomStepFactor = event->angleDelta().y() > 0 ? ZOOM_STEP : 1.0f / ZOOM_STEP;

    QPointF delta = (1.0f - zoomStepFactor) * event->posF();

    m_viewportTransformMatrix.translate(delta.x(),delta.y());
    m_viewportTransformMatrix.scale(zoomStepFactor);
}


/******************************************************************************
*   Перемещение камеры в стороны
******************************************************************************/
void Ortho2DCamera::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton)
        return;

    QPointF delta = m_lastMousePos - event->pos();
    m_viewportTransformMatrix.translate(delta.x(),delta.y());
    m_lastMousePos = event->pos();
}


/******************************************************************************
*   Начало перемещения камеры в стороны
******************************************************************************/
void Ortho2DCamera::mousePressEvent(QMouseEvent *event)
{
    m_lastMousePos = event->pos();
}

void Ortho2DCamera::mouseReleaseEvent(QMouseEvent *event)
{

}

void Ortho2DCamera::keyPressEvent(QKeyEvent *event)
{

}

void Ortho2DCamera::keyReleaseEvent(QKeyEvent *event)
{

}
