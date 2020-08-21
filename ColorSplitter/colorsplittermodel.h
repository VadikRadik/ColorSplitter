#ifndef COLORSPLITTERMODEL_H
#define COLORSPLITTERMODEL_H

#include <unordered_map>
#include <list>
#include <memory>

#include <QImage>

#include "icolorsplitterview.h"

#include "emodelupdates.h"

/******************************************************************************
*
*   Model of the application (MVC)
*
******************************************************************************/
class ColorSplitterModel
{
public:
    ColorSplitterModel();

    const QImage & image() const;
    void resetImage(const QString & imagePath);
    void setCutFrame(const QRect & frameRect);
    const std::unordered_map<QRgb, int> & decomposedColors() const;
    const QRect &cutFrame() const;

    void subscribeView(std::shared_ptr<IColorSplitterView> view);

private:
    void decompose();
    void notify(EModelUpdates stateChanged) const;
    QRect imageRect() const;

private:
    QImage m_image;
    QRect m_cutFrame;
    std::unordered_map<QRgb,int> m_decomposedColors;
    std::list<std::weak_ptr<IColorSplitterView>> m_views;

    static constexpr int BUCKETS_COUNT = 2000000;
};

#endif // COLORSPLITTERMODEL_H
