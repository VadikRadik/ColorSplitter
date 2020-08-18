#ifndef IWIDGETINPUTHANDLER_H
#define IWIDGETINPUTHANDLER_H

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

/******************************************************************************
*
*   User's input handler interface
*
******************************************************************************/
class IWidgetInputHandler
{
public:
    virtual void wheelEvent         (QWheelEvent *event) = 0;
    virtual void mouseMoveEvent     (QMouseEvent *event) = 0;
    virtual void mousePressEvent    (QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent  (QMouseEvent *event) = 0;
    virtual void keyPressEvent      (QKeyEvent *event)   = 0;
    virtual void keyReleaseEvent    (QKeyEvent *event)   = 0;
};

#endif // IWIDGETINPUTHANDLER_H
