#ifndef IMAGESOURCESCONTROLLER_H
#define IMAGESOURCESCONTROLLER_H

#include "colorsplittermodel.h"

class ImageSourcesController
{
public:
    ImageSourcesController(ColorSplitterModel &model);

    void setImage(const QString & path);

private:
    ColorSplitterModel & m_model;
};

#endif // IMAGESOURCESCONTROLLER_H
