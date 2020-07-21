#ifndef COLORDIAGRAMVIEW_H
#define COLORDIAGRAMVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"

class ColorDiagramView : public IColorSplitterView
{
public:
    ColorDiagramView();

    virtual QWidget *createWidget() const override;
    virtual void update(SplitterViewModel * model) override;

private:
    OpenGLWidget * m_imegeWidget;
    std::weak_ptr<Scene> m_scene;
};

#endif // COLORDIAGRAMVIEW_H
