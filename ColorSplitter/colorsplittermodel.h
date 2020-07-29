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
    void resetImage(const QString & imagePath);//const QImage &image);
    void setCutFrame(const QMargins & margins);

    std::unordered_map<QRgb, int> decomposedColors() const;
    void decompose();

    QMargins cutFrame() const; // для проверки на нулл в апдейте вьюхи имаджа

    void subscribeView(std::shared_ptr<IColorSplitterView> view);

private:
    void notify(EModelUpdates stateChanged) const;
    QMargins imageMargins() const;

private:
    QImage m_image;
    QMargins m_cutFrame;
    std::unordered_map<QRgb,int> m_decomposedColors;
    std::list<std::shared_ptr<IColorSplitterView>> m_views;
};

#endif // COLORSPLITTERMODEL_H
