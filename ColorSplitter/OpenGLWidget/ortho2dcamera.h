#ifndef ORTHO2DCAMERA_H
#define ORTHO2DCAMERA_H

#include "icamera.h"

/******************************************************************************
*
*   Камера для 2D сцены
*
******************************************************************************/
class Ortho2DCamera : public ICamera
{
public:
    Ortho2DCamera() = default;

    virtual void resizeView(int width, int height) override;
    virtual QMatrix4x4 projectionMatrix()         const override;
    virtual QMatrix4x4 viewMatrix()               const override;

    virtual void wheelEvent     (QWheelEvent *event)    override;
    virtual void mouseMoveEvent (QMouseEvent *event)    override;
    virtual void mousePressEvent(QMouseEvent *event)    override;
    virtual void keyPressEvent  (QKeyEvent *event)      override;
    virtual void keyReleaseEvent(QKeyEvent *event)      override;

private:
    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_viewportTransformMatrix;
    QRectF m_viewRect;

    QPointF m_lastMousePos;

    const float ZOOM_STEP = 0.77f;
};

#endif // ORTHO2DCAMERA_H
