#ifndef COLORDIAGRAMVIEW_H
#define COLORDIAGRAMVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"
#include "colordiagramscene.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

class ColorDiagramView : public IColorSplitterView
{
public:
    ColorDiagramView();

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    QVBoxLayout *createControls() const;

private:
    OpenGLWidget * m_diagramWidget;
    std::weak_ptr<ColorDiagramScene> m_scene;
    QRadioButton * m_cubeShape;
    QRadioButton * m_icosahedronShape;
    QCheckBox * m_lightSwitch;
};

#endif // COLORDIAGRAMVIEW_H
