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
}

void ImageScene::changeImage(const QImage &image)
{
    makeCurrentContext();

    if (!m_image.expired())
        removeObject(m_image.lock());

    std::shared_ptr<IDrawable> newImage = std::make_shared<RasterImage>(image,m_rasterImageShader);
    m_image = newImage;
    addObject(newImage);
}
