#ifndef IMAGESOURCESVIEW_H
#define IMAGESOURCESVIEW_H

#include <QListView>
#include <QPushButton>
#include <QString>
#include <QRadioButton>
#include <QHBoxLayout>

#include "icolorsplitterview.h"

class ImageSourcesView : public IColorSplitterView
{
public:
    ImageSourcesView();

    ImageSourcesView(const ImageSourcesView&)            = delete;
    ImageSourcesView(ImageSourcesView&&)                 = delete;

    ImageSourcesView& operator=(const ImageSourcesView&) = delete;
    ImageSourcesView& operator=(ImageSourcesView&&)      = delete;

    virtual QWidget *createWidget() const override;

private:
    QHBoxLayout * createControls() const;

private:
    const QString LOAD_IMAGES_BUTTON_CAPTION = "Открыть список изображений";
    const QString SHOW_IMAGE_PATH = "Путь";
    const QString SHOW_FILE_NAME = "Имя файла";
    const QString WAY_TO_SHOW_CAPTION = "Отображать в списке";

    QPushButton * m_loadImagesButton;
    QListView * m_imageSourcesView;
    QRadioButton * m_showPath;
    QRadioButton * m_showName;
};

#endif // IMAGESOURCESVIEW_H
