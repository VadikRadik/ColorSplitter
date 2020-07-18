#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <QOpenGLContext>

#include "idrawable.h"
#include "icamera.h"

/******************************************************************************
*
*   Сцена с рисуемыми объектами
*
******************************************************************************/
class Scene
{
public:
    Scene();

    void bindDrawContext(QOpenGLContext *context);
    void setCamera(ICamera * camera);

    void draw();
    void resizeView(int width, int height);

    void addObject(std::shared_ptr<IDrawable> obj);
    void removeObject(std::shared_ptr<IDrawable> obj);

    void flushObjects();

    void wheelEvent     (QWheelEvent *event);
    void mouseMoveEvent (QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent  (QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    std::unique_ptr<ICamera> m_camera;
    QOpenGLContext * m_openGLContext;
    std::list<std::shared_ptr<IDrawable>> m_sceneObjects;
};

#endif // SCENE_H
