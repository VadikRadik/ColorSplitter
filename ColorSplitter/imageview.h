#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"

/******************************************************************************
*
*   Представление изображения
*
******************************************************************************/
class ImageView : public IColorSplitterView
{
public:
    ImageView();

    ImageView(const ImageView&)            = delete;
    ImageView(ImageView&&)                 = delete;

    ImageView& operator=(const ImageView&) = delete;
    ImageView& operator=(ImageView&&)      = delete;

    virtual QWidget *createWidget() const override;
    virtual void update(SplitterViewModel * model) override;

private:
    OpenGLWidget * m_imegeWidget;
};

#endif // IMAGEVIEW_H
