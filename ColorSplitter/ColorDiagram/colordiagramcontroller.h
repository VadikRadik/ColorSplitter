#ifndef COLORDIAGRAMCONTROLLER_H
#define COLORDIAGRAMCONTROLLER_H

#include <memory>

#include "colorsplittermodel.h"
#include "colordiagramscene.h"


/******************************************************************************
*
*   Controller for the color diagram module
*
******************************************************************************/
class ColorDiagramController
{
public:
    ColorDiagramController(ColorSplitterModel &model);

    void fillDiagram();
    void switchLight(bool light);
    void setShape(EDiagramDotShape shape);
    void flushDiagram();

    void bindScene(std::shared_ptr<ColorDiagramScene> scene);

private:
    ColorSplitterModel & m_model;
    std::weak_ptr<ColorDiagramScene> m_scene;
};

#endif // COLORDIAGRAMCONTROLLER_H
