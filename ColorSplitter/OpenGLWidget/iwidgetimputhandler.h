#ifndef IWIDGETIMPUTHANDLER_H
#define IWIDGETIMPUTHANDLER_H

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class IWidgetImputHandler
{
public:
    virtual void wheelEvent         (QWheelEvent *event) = 0;
    virtual void mouseMoveEvent     (QMouseEvent *event) = 0;
    virtual void mousePressEvent    (QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent  (QMouseEvent *event) = 0;
    virtual void keyPressEvent      (QKeyEvent *event)   = 0;
    virtual void keyReleaseEvent    (QKeyEvent *event)   = 0;
};

#endif // IWIDGETIMPUTHANDLER_H
