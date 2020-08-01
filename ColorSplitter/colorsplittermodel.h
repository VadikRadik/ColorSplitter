#ifndef COLORSPLITTERMODEL_H
#define COLORSPLITTERMODEL_H

#include <unordered_map>
#include <list>
#include <memory>

#include <QImage>

#include "icolorsplitterview.h"

#include "emodelupdates.h"

class ColorSplitterModel
{
public:
    ColorSplitterModel();

    const QImage & image() const;
    void resetImage(const QString & imagePath);
    void setCutFrame(const QRect & frameRect);
    const std::unordered_map<QRgb, int> & decomposedColors() const;
    QRect cutFrame() const; // для проверки на нулл в апдейте вьюхи имаджа

    void subscribeView(std::shared_ptr<IColorSplitterView> view);

private:
    void decompose();
    void notify(EModelUpdates stateChanged) const;
    QRect imageRect() const;

private:
    QImage m_image;
    QRect m_cutFrame;
    std::unordered_map<QRgb,int> m_decomposedColors;
    std::list<std::shared_ptr<IColorSplitterView>> m_views;
};

#endif // COLORSPLITTERMODEL_H
