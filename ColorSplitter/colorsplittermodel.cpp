#include "colorsplittermodel.h"

ColorSplitterModel::ColorSplitterModel()
    : m_image()
    , m_cutFrame()
    , m_decomposedColors()
    , m_views()
{
    m_decomposedColors.reserve(std::numeric_limits<unsigned int>::max()/64);
}


/******************************************************************************
*   Геттер изображения
******************************************************************************/
const QImage &ColorSplitterModel::image() const
{
    return m_image;
}


/******************************************************************************
*   Переключение изображения
******************************************************************************/
void ColorSplitterModel::resetImage(const QString & imagePath)
{
    m_image = QImage(imagePath);
    notify(EModelUpdates::IMAGE_CHANGED);

    setCutFrame(QMargins());
}


/******************************************************************************
*   Установка рассматриваемой области изображения
******************************************************************************/
void ColorSplitterModel::setCutFrame(const QMargins &margins)
{
    m_cutFrame = margins;
    notify(EModelUpdates::CUT_FRAME_CHANGED);

    decompose();
    notify(EModelUpdates::IMAGE_DECOMPOSED);
}


/******************************************************************************
*   Геттер результирующего разбиения
******************************************************************************/
const std::unordered_map<QRgb, int> &ColorSplitterModel::decomposedColors() const
{
    return m_decomposedColors;
}


/******************************************************************************
*   Попиксельное разбиение изображения на составляющие цвета
******************************************************************************/
void ColorSplitterModel::decompose()
{
    m_decomposedColors.clear();
    QMargins frame = imageMargins();

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
*   Геттер рассматриваемой области
******************************************************************************/
QMargins ColorSplitterModel::cutFrame() const
{
    return m_cutFrame;
}


/******************************************************************************
*   Подписка представлений на изменения модели
******************************************************************************/
void ColorSplitterModel::subscribeView(std::shared_ptr<IColorSplitterView> view)
{
    m_views.push_back(view);
}


/******************************************************************************
*   Уведомление моделей об изменениях состояния моделей
******************************************************************************/
void ColorSplitterModel::notify(EModelUpdates stateChanged) const
{
    for (auto it = m_views.cbegin(); it != m_views.cend(); ++it)
        (*it)->update(this, stateChanged);
}


/******************************************************************************
*   Границы изображения с учётом границ рассматриваемой области
******************************************************************************/
QMargins ColorSplitterModel::imageMargins() const
{
    QMargins result;
    if (m_cutFrame.isNull())
    {
        result = QMargins(0,0,m_image.width(),m_image.height());
    }
    else
    {
        int left = std::max(0,m_cutFrame.left());
        int right = std::min(m_image.width(),m_cutFrame.right());
        int top = std::max(0,m_cutFrame.top());
        int bottom = std::min(m_image.height(),m_cutFrame.bottom());
        result = QMargins(left,top,right,bottom);
    }
    return result;
}

