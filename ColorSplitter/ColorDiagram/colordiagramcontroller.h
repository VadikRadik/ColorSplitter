#ifndef COLORDIAGRAMCONTROLLER_H
#define COLORDIAGRAMCONTROLLER_H

#include <memory>

#include "colorsplittermodel.h"
#include "colordiagramscene.h"

#include <QTimer>


/******************************************************************************
*
*   Controller for the color diagram module
*
******************************************************************************/
class ColorDiagramController : public QObject
{
    Q_OBJECT
public:
    ColorDiagramController(ColorSplitterModel &model);

    void fillDiagram();
    void switchLight(bool light);
    void setShape(EDiagramDotShape shape);
    void flushDiagram();

    void bindScene(std::shared_ptr<ColorDiagramScene> scene);

signals:
    void diagramChanged();

private:
    bool checkUpdateDiagram();

private:
    ColorSplitterModel & m_model;
    std::weak_ptr<ColorDiagramScene> m_scene;

    QTimer m_timer;
    static const int TIMER_PERIOD = 50;
};

#endif // COLORDIAGRAMCONTROLLER_H
