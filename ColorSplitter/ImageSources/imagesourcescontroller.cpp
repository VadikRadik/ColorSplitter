#include "imagesourcescontroller.h"

ImageSourcesController::ImageSourcesController(ColorSplitterModel &model)
    : m_model(model)
{

}

void ImageSourcesController::setImage(const QString &path)
{
    m_model.resetImage(path);
}
