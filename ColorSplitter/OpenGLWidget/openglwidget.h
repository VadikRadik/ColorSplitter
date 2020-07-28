#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions>

#include "abstractscene.h"

/******************************************************************************
*
*   Реализация QOpenGLWidget
*
******************************************************************************/
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWidget(std::shared_ptr<AbstractScene> scene, QWidget *parent = 0);
    ~OpenGLWidget();

protected:
    void initializeGL   ()                      override;
    void paintGL        ()                      override;
    void resizeGL       (int width, int height) override;
    void wheelEvent     (QWheelEvent *event)    override;
    void mouseMoveEvent (QMouseEvent *event)    override;
    void mousePressEvent(QMouseEvent *event)    override;
    void keyPressEvent  (QKeyEvent *event)      override;
    void keyReleaseEvent(QKeyEvent *event)      override;

private:
    std::shared_ptr<AbstractScene> m_scene;
};

#endif // OPENGLWIDGET_H
