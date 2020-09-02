#include "colorsplittermodel.h"

ColorSplitterModel::ColorSplitterModel()
    : m_image()
    , m_cutFrame()
    , m_decomposedColors()
    , m_views()
{
    m_decomposedColors.reserve(BUCKETS_COUNT);
}


/******************************************************************************
*   Image getter
******************************************************************************/
const QImage &ColorSplitterModel::image() const
{
    return m_image;
}


/******************************************************************************
*   Changes an image
******************************************************************************/
void ColorSplitterModel::resetImage(const QString & imagePath)
{
    m_image = QImage(imagePath);
    notify(EModelUpdates::IMAGE_CHANGED);

    setCutFrame(QRect());
}


/******************************************************************************
*   Sets the exploring frame
******************************************************************************/
void ColorSplitterModel::setCutFrame(const QRect &frameRect)
{
    m_cutFrame = frameRect;

    m_decomposedColors.clear();

    notify(EModelUpdates::CUT_FRAME_CHANGED);
}


/******************************************************************************
*   Gets the color splitting result
******************************************************************************/
const std::unordered_map<QRgb, int> &ColorSplitterModel::decomposedColors()
{
    if (m_decomposedColors.empty())
        decompose();

    return m_decomposedColors;
}


/******************************************************************************
*   Counts all colors of the image
******************************************************************************/
void ColorSplitterModel::decompose()
{
    QRect frame = imageRect();

    for (int y = frame.top(); y < frame.bottom(); ++y){
        QRgb* line = reinterpret_cast<QRgb*>(m_image.scanLine(y)) + frame.left();
        for (int x = frame.left(); x < frame.right(); ++x){
            if (m_decomposedColors.find(*line) == m_decomposedColors.end())
                m_decomposedColors[*line] = 1;
            else
                m_decomposedColors[*line] += 1;
            line++;
        }
    }
}


/******************************************************************************
*   Gets the exploring frame
******************************************************************************/
const QRect &ColorSplitterModel::cutFrame() const
{
    return m_cutFrame;
}


/******************************************************************************
*   Subscribes views for model's state changes
******************************************************************************/
void ColorSplitterModel::subscribeView(std::shared_ptr<IColorSplitterView> view)
{
    m_views.push_back(view);
}


/******************************************************************************
*   Notifies views for model's state changes
******************************************************************************/
void ColorSplitterModel::notify(EModelUpdates stateChanged) const
{
    for (auto it = m_views.cbegin(); it != m_views.cend(); ++it) {
        if (!it->expired())
            it->lock()->update(this, stateChanged);
    }
}


/******************************************************************************
*   Bounds of the image rectangle with the exploring frame's bounds
******************************************************************************/
QRect ColorSplitterModel::imageRect() const
{
    QRect result;

    if (m_cutFrame.isNull())
        result = QRect(QPoint(0,0),QPoint(m_image.width(),m_image.height()));
    else
        result = m_cutFrame.intersected(m_image.rect());

    return result;
}

