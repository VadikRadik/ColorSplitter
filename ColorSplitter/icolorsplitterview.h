#ifndef ICOLORSPLITTERVIEW_H
#define ICOLORSPLITTERVIEW_H

#include <QWidget>

#include "emodelupdates.h"
//#include "colorsplittermodel.h"
class ColorSplitterModel;


/******************************************************************************
*
*   Интерфейс для представлений приложения (View в MVC)
*
******************************************************************************/
class IColorSplitterView
{
public:
    virtual QWidget * createWidget() const          = 0;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange)  = 0;
};

#endif // ICOLORSPLITTERVIEW_H
