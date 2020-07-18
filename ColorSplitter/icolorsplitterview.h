#ifndef ICOLORSPLITTERVIEW_H
#define ICOLORSPLITTERVIEW_H

#include <QWidget>

class SplitterViewModel;

/******************************************************************************
*
*   Интерфейс для представлений приложения (View в MVC)
*
******************************************************************************/
class IColorSplitterView
{
public:
    virtual QWidget * createWidget() const          = 0;
    virtual void update(SplitterViewModel * model)  = 0;
};

#endif // ICOLORSPLITTERVIEW_H
