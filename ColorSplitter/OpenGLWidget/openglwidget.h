#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions>

#include "scene.h"

/******************************************************************************
*
*   Реализация QOpenGLWidget
*
******************************************************************************/
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

    void addToScene(std::shared_ptr<IDrawable> obj);

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
    Scene m_scene;
};

#endif // OPENGLWIDGET_H
