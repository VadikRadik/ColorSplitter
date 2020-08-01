#include "centred3deulercamera.h"

#include<QtMath>

Centred3DEulerCamera::Centred3DEulerCamera()
    : m_phi(0.0f)
    , m_theta(M_PI_2)
    , m_eye(0.0f,0.0f,4.0f)
    , m_center(0.0f,0.5f,0.0f)
    , m_viewRect()
    , m_lastMousePos()
    , m_fov(45.0f)
{
    calcEyePosition();
}

void Centred3DEulerCamera::calcEyePosition()
{
    m_eye = QVector3D(EYE_R*qSin(m_phi)*qSin(m_theta), EYE_R*qCos(m_theta), EYE_R*qCos(m_phi)*qSin(m_theta));
    m_eye += m_center;
}

/******************************************************************************
*   Обработка изменения вьюпорта
******************************************************************************/
void Centred3DEulerCamera::resizeView(int width, int height)
{
    m_viewRect.setSize(QSizeF(width,height));
}


/******************************************************************************
*   Возврат матрицы проекции
******************************************************************************/
QMatrix4x4 Centred3DEulerCamera::projectionMatrix() const
{
    QMatrix4x4 projection;
    projection.perspective(m_fov,float(m_viewRect.width())/m_viewRect.height(),PROJECTION_NEAR_PLANE,PROJECTION_FAR_PLANE);
    return projection;
}


/******************************************************************************
*   Возврат матрицы вью
******************************************************************************/
QMatrix4x4 Centred3DEulerCamera::viewMatrix() const
{
    QMatrix4x4 view;
    view.lookAt(m_eye,m_center,LOOK_AT_UP);
    return view;
}


/******************************************************************************
*   Вектор направления камеры
******************************************************************************/
QVector3D Centred3DEulerCamera::viewDirection() const
{
    return m_eye.normalized();
}

QVector3D Centred3DEulerCamera::projectPoint(QPoint point) const
{
    return QVector3D();// todo
}


/******************************************************************************
*   Изменение угла обзора
******************************************************************************/
void Centred3DEulerCamera::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().isNull())
        return;

    float newFov = event->angleDelta().y() > 0 ? m_fov - FOV_STEP : m_fov + FOV_STEP;
    if ( newFov < FOV_MAX && newFov > FOV_MIN )
        m_fov = newFov;
}


/******************************************************************************
*   Вращение камеры
******************************************************************************/
void Centred3DEulerCamera::mouseMoveEvent(QMouseEvent *event)
{
    QPointF delta = m_lastMousePos - event->pos();
    delta *= ROTATION_SPEED;
    m_phi += delta.x();
    if (m_theta + delta.y() < M_PI && m_theta + delta.y() > 0)
        m_theta = m_theta + delta.y();

    if (event->buttons() & Qt::RightButton ||
        event->buttons() & Qt::RightButton & Qt::LeftButton)
        m_theta = M_PI_2;

    calcEyePosition();

    m_lastMousePos = event->pos();
}


/******************************************************************************
*   Начало вращения камеры
******************************************************************************/
void Centred3DEulerCamera::mousePressEvent(QMouseEvent *event)
{
    m_lastMousePos = event->pos();
}

void Centred3DEulerCamera::mouseReleaseEvent(QMouseEvent *event)
{

}

void Centred3DEulerCamera::keyPressEvent(QKeyEvent *event)
{

}

void Centred3DEulerCamera::keyReleaseEvent(QKeyEvent *event)
{

}
