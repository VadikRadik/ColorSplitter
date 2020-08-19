#include "imagescene.h"
#include "DrawableObjects/rasterimage.h"
#include "DrawableObjects/lineframe.h"

ImageScene::ImageScene(ICamera * camera)
    : AbstractScene(camera)
    , m_rasterImageShader(nullptr)
    , m_topLeftFrame()
    , m_bottomRightFrame()
{

}


/******************************************************************************
*   Creates shaders
******************************************************************************/
void ImageScene::initialize()
{
    m_rasterImageShader = createShader(":/shaders/rasterImage.vsh",":/shaders/rasterImage.fsh",QString());
    m_lineFrameShader = createShader(":/shaders/line.vsh",":/shaders/line.fsh",QString());
}


/******************************************************************************
*   Changes images
******************************************************************************/
void ImageScene::changeImage(const QImage &image)
{
    makeCurrentContext();

    if (!m_image.expired())
        removeObject(m_image.lock());

    std::shared_ptr<IDrawable> newImage = std::make_shared<RasterImage>(image,m_rasterImageShader);
    m_image = newImage;
    addObject(newImage);
}


/******************************************************************************
*   Changes the exploring frame geometry
******************************************************************************/
void ImageScene::expandFrame(QPoint position)
{
    if (!m_frame.expired()) {
        QVector3D projectedVector = m_camera->projectPoint(position);
        QPointF projectedPosition(projectedVector.x(),projectedVector.y());
        m_frame.lock()->expandFrame(projectedPosition);

        m_bottomRightFrame = projectedPosition.toPoint();
    }
}


/******************************************************************************
*   Creates an exploring frame
******************************************************************************/
void ImageScene::createFrame(QPoint position)
{
    removeFrame();

    QVector3D projectedVector = m_camera->projectPoint(position);
    QPointF projectedPosition(projectedVector.x(),projectedVector.y());

    std::shared_ptr<LineFrame> newFrame = std::make_shared<LineFrame>(m_lineFrameShader,projectedPosition);
    m_frame = newFrame;
    addObject(newFrame);

    m_topLeftFrame = projectedPosition.toPoint();
    m_bottomRightFrame = m_topLeftFrame;
}


/******************************************************************************
*   Removes the exploring frame
******************************************************************************/
void ImageScene::removeFrame()
{
    makeCurrentContext();

    if (!m_frame.expired())
        removeObject(m_frame.lock());

    m_topLeftFrame = QPoint();
    m_bottomRightFrame = QPoint();
}


/******************************************************************************
*   Returns exploring frame's coordinates in the world space
******************************************************************************/
QRect ImageScene::getFrameRect() const
{
    std::pair<int,int> xMinMax = std::minmax(m_topLeftFrame.x(),m_bottomRightFrame.x());
    std::pair<int,int> yMinMax = std::minmax(m_topLeftFrame.y(),m_bottomRightFrame.y());
    return QRect(QPoint(xMinMax.first, yMinMax.first), QPoint(xMinMax.second, yMinMax.second));
}
