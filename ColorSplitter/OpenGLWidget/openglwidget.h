#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions>

#include "abstractscene.h"
#include "iwidgetimputhandler.h"

/******************************************************************************
*
*   Реализация QOpenGLWidget
*
******************************************************************************/
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWidget(std::shared_ptr<AbstractScene> scene, std::shared_ptr<IWidgetImputHandler> controller = nullptr, QWidget *parent = 0);
    ~OpenGLWidget();

protected:
    virtual void initializeGL       ()                      override;
    virtual void paintGL            ()                      override;
    virtual void resizeGL           (int width, int height) override;
    virtual void wheelEvent         (QWheelEvent *event)    override;
    virtual void mouseMoveEvent     (QMouseEvent *event)    override;
    virtual void mousePressEvent    (QMouseEvent *event)    override;
    virtual void mouseReleaseEvent  (QMouseEvent *event)    override;
    virtual void keyPressEvent      (QKeyEvent *event)      override;
    virtual void keyReleaseEvent    (QKeyEvent *event)      override;

private:
    std::shared_ptr<AbstractScene> m_scene;
    std::shared_ptr<IWidgetImputHandler> m_controller;
};

#endif // OPENGLWIDGET_H
