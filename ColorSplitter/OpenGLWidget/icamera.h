#ifndef ICAMERA_H
#define ICAMERA_H

#include <QMatrix4x4>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>

/******************************************************************************
*
*   A camera interface. Handles input events from a widget and modifies
*   view and projection matrices
*
******************************************************************************/
class ICamera
{
public:
    virtual~ICamera(){}

    virtual void resizeView(int width, int height)      = 0;
    virtual QMatrix4x4 projectionMatrix()         const = 0;
    virtual QMatrix4x4 viewMatrix()               const = 0;
    virtual QVector3D viewDirection()             const = 0;
    virtual QVector3D projectPoint(QPoint point)  const = 0;

    virtual void wheelEvent         (QWheelEvent *event)    = 0;
    virtual void mouseMoveEvent     (QMouseEvent *event)    = 0;
    virtual void mousePressEvent    (QMouseEvent *event)    = 0;
    virtual void mouseReleaseEvent  (QMouseEvent *event)    = 0;
    virtual void keyPressEvent      (QKeyEvent *event)      = 0;
    virtual void keyReleaseEvent    (QKeyEvent *event)      = 0;
};

#endif // ICAMERA_H
