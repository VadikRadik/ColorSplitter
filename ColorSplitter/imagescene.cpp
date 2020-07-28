#include "imagescene.h"
#include "DrawableObjects/rasterimage.h"

ImageScene::ImageScene(ICamera * camera)
    : AbstractScene(camera)
    , m_rasterImageShader(nullptr)
{

}

void ImageScene::initialize()
{
    m_rasterImageShader = createShader(":/shaders/rasterImage.vsh",":/shaders/rasterImage.fsh",QString());
    setImage(QImage("f:/tempos/снимок001.png"));
}

void ImageScene::setImage(const QImage &image)
{
    makeCurrentContext();
    addObject(std::make_shared<RasterImage>(image,m_rasterImageShader));
}
