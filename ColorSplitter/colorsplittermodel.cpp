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

    setCutFrame(QRect());
}


/******************************************************************************
*   Установка рассматриваемой области изображения
******************************************************************************/
void ColorSplitterModel::setCutFrame(const QRect &frameRect)
{
    m_cutFrame = frameRect;
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
*   Геттер рассматриваемой области
******************************************************************************/
QRect ColorSplitterModel::cutFrame() const
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
QRect ColorSplitterModel::imageRect() const
{
    QRect result;

    if (m_cutFrame.isNull())
        result = QRect(QPoint(0,0),QPoint(m_image.width(),m_image.height()));
    else
        result = m_cutFrame.intersected(m_image.rect());

    return result;
}

