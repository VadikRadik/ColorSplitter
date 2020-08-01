#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <memory>
#include <QOpenGLContext>

#include "idrawable.h"
#include "icamera.h"

/******************************************************************************
*
*   Сцена с рисуемыми объектами
*
******************************************************************************/
class AbstractScene
{
public:
    AbstractScene(ICamera * camera);
    virtual~AbstractScene() {}

    void bindDrawContext(QOpenGLContext *context);
    //void setCamera(ICamera * camera);

    void draw();
    void resizeView(int width, int height);

    void addObject(std::shared_ptr<IDrawable> obj);
    void removeObject(std::shared_ptr<IDrawable> obj);

    void flushObjects();

    void wheelEvent         (QWheelEvent *event);
    void mouseMoveEvent     (QMouseEvent *event);
    void mousePressEvent    (QMouseEvent *event);
    void keyPressEvent      (QKeyEvent *event);
    void keyReleaseEvent    (QKeyEvent *event);
    void mouseReleaseEvent  (QMouseEvent *event);

    virtual void initialize() = 0;

protected:
    std::shared_ptr<QOpenGLShaderProgram> createShader(const QString & vertexShaderPath,
                                                       const QString & fragmentShaderPath,
                                                       const QString & geometryShaderPath);
    void makeCurrentContext();

protected:
    QOpenGLContext * m_openGLContext;
    std::unique_ptr<ICamera> m_camera;

private:
    QSurface * m_cotextSurface;
    std::list<std::shared_ptr<IDrawable>> m_sceneObjects;
};

#endif // ABSTRACTSCENE_H
