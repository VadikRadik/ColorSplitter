#ifndef ICOLORSPLITTERVIEW_H
#define ICOLORSPLITTERVIEW_H

#include <QWidget>

#include "emodelupdates.h"

class ColorSplitterModel;

/******************************************************************************
*
*   View interface (MVC)
*
******************************************************************************/
class IColorSplitterView
{
public:
    virtual ~IColorSplitterView() = default;

    virtual QWidget * createWidget() const = 0;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) = 0;
};

#endif // ICOLORSPLITTERVIEW_H
