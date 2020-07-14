#ifndef ICOLORSPLITTERVIEW_H
#define ICOLORSPLITTERVIEW_H

#include <QWidget>

class IColorSplitterView
{
public:
    virtual QWidget * createWidget() const = 0;
};

#endif // ICOLORSPLITTERVIEW_H
