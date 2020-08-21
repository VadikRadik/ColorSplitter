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


/******************************************************************************
*   Handles changes of viewport's size
******************************************************************************/
void Centred3DEulerCamera::resizeView(int width, int height)
{
    m_viewRect.setSize(QSizeF(width,height));
}


/******************************************************************************
*   Returns the projection matrix
******************************************************************************/
QMatrix4x4 Centred3DEulerCamera::projectionMatrix() const
{
    QMatrix4x4 projection;
    projection.perspective(m_fov,float(m_viewRect.width())/m_viewRect.height(),PROJECTION_NEAR_PLANE,PROJECTION_FAR_PLANE);
    return projection;
}


/******************************************************************************
*   Returns the view matrix
******************************************************************************/
QMatrix4x4 Centred3DEulerCamera::viewMatrix() const
{
    QMatrix4x4 view;
    view.lookAt(m_eye,m_center,LOOK_AT_UP);
    return view;
}


/******************************************************************************
*   Returns the view direction
******************************************************************************/
QVector3D Centred3DEulerCamera::viewDirection() const
{
    return m_eye.normalized();
}


/******************************************************************************
*   Returns the world coordinates
******************************************************************************/
QVector3D Centred3DEulerCamera::projectPoint(QPoint point) const
{
    return QVector3D();// todo
}


/******************************************************************************
*   Changes the field of view
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
*   Rotates the camera
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
*   Begining of rotation. Memorizes the start mouse position
******************************************************************************/
void Centred3DEulerCamera::mousePressEvent(QMouseEvent *event)
{
    m_lastMousePos = event->pos();
}

void Centred3DEulerCamera::mouseReleaseEvent(QMouseEvent *event)
{
    // do nothing
}

void Centred3DEulerCamera::keyPressEvent(QKeyEvent *event)
{
    // do nothing
}

void Centred3DEulerCamera::keyReleaseEvent(QKeyEvent *event)
{
    // do nothing
}

/******************************************************************************
*   Calculating of the eye position
******************************************************************************/
void Centred3DEulerCamera::calcEyePosition()
{
    m_eye = QVector3D(EYE_R*qSin(m_phi)*qSin(m_theta), EYE_R*qCos(m_theta), EYE_R*qCos(m_phi)*qSin(m_theta));
    m_eye += m_center;
}
