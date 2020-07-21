#ifndef CENTRED3DEULERCAMERA_H
#define CENTRED3DEULERCAMERA_H

#include "icamera.h"

class Centred3DEulerCamera : public ICamera
{
public:
    Centred3DEulerCamera();

    virtual void resizeView(int width, int height) override;
    virtual QMatrix4x4 projectionMatrix()         const override;
    virtual QMatrix4x4 viewMatrix()               const override;
    virtual QVector3D viewDirection()             const override;

    virtual void wheelEvent     (QWheelEvent *event)    override;
    virtual void mouseMoveEvent (QMouseEvent *event)    override;
    virtual void mousePressEvent(QMouseEvent *event)    override;
    virtual void keyPressEvent  (QKeyEvent *event)      override;
    virtual void keyReleaseEvent(QKeyEvent *event)      override;

private:
    void calcEyePosition();

private:
    float m_phi;
    float m_theta;
    float m_fov;
    QVector3D m_eye;
    QVector3D m_center;
    QRectF m_viewRect;
    QPointF m_lastMousePos;

    const float FOV_STEP = 3.0f;
    const float FOV_MAX = 120.0f;
    const float FOV_MIN = 1.0f;
    const float EYE_R = 4.0f;
    const float PROJECTION_NEAR_PLANE = 0.1f;
    const float PROJECTION_FAR_PLANE = 10.0f;
    const float ROTATION_SPEED = 0.01f;
    const QVector3D LOOK_AT_UP = QVector3D(0.0f,1.0f,0.0f);
};

#endif // CENTRED3DEULERCAMERA_H
