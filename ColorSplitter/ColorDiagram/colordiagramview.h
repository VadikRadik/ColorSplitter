#ifndef COLORDIAGRAMVIEW_H
#define COLORDIAGRAMVIEW_H

#include "icolorsplitterview.h"
#include "OpenGLWidget/openglwidget.h"
#include "colordiagramscene.h"
#include "colordiagramcontroller.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

class ColorDiagramView : public IColorSplitterView
{
public:
    ColorDiagramView(std::shared_ptr<ColorDiagramController> controller);

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    QVBoxLayout *createControls() const;
    void createLogic(QWidget* widget) const;

private:
    OpenGLWidget * m_diagramWidget;
    std::weak_ptr<ColorDiagramScene> m_scene;
    QRadioButton * m_tetrahedronShape;
    QRadioButton * m_cubeShape;
    QRadioButton * m_octahedronShape;
    QRadioButton * m_icosahedronShape;
    QCheckBox * m_lightSwitch;
    std::shared_ptr<ColorDiagramController> m_controller;
};

#endif // COLORDIAGRAMVIEW_H
