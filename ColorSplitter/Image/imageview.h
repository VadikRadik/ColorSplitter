#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"
#include "imagescene.h"
#include "imagecontroller.h"

/******************************************************************************
*
*   Представление изображения
*
******************************************************************************/
class ImageView : public IColorSplitterView
{
public:
    ImageView(std::shared_ptr<ImageController> controller);

    ImageView(const ImageView&)            = delete;
    ImageView(ImageView&&)                 = delete;

    ImageView& operator=(const ImageView&) = delete;
    ImageView& operator=(ImageView&&)      = delete;

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    OpenGLWidget * m_imegeWidget;
    std::weak_ptr<ImageScene> m_scene;
};

#endif // IMAGEVIEW_H
