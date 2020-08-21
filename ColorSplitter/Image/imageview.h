#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"
#include "imagescene.h"
#include "imagecontroller.h"

/******************************************************************************
*
*   The image views
*
******************************************************************************/
class ImageView : public IColorSplitterView
{
public:
    ImageView(std::shared_ptr<ImageController> controller);

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    OpenGLWidget * m_imegeWidget;
    std::weak_ptr<ImageScene> m_scene;
};

#endif // IMAGEVIEW_H
