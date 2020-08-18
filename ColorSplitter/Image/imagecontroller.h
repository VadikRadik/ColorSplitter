#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include "OpenGLWidget/iwidgetinputhandler.h"
#include "imagescene.h"
#include "colorsplittermodel.h"

class ImageController : public IWidgetInputHandler
{
public:
    ImageController(ColorSplitterModel &model);

    void bindScene(std::shared_ptr<ImageScene> scene);

    virtual void wheelEvent         (QWheelEvent *event) override;
    virtual void mouseMoveEvent     (QMouseEvent *event) override;
    virtual void mousePressEvent    (QMouseEvent *event) override;
    virtual void mouseReleaseEvent  (QMouseEvent *event) override;
    virtual void keyPressEvent      (QKeyEvent *event)   override;
    virtual void keyReleaseEvent    (QKeyEvent *event)   override;

private:
    ColorSplitterModel & m_model;
    std::weak_ptr<ImageScene> m_scene;
};

#endif // IMAGECONTROLLER_H
