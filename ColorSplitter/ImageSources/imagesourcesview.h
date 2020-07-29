#ifndef IMAGESOURCESVIEW_H
#define IMAGESOURCESVIEW_H

#include <QListView>
#include <QPushButton>
#include <QString>
#include <QRadioButton>
#include <QHBoxLayout>

#include "icolorsplitterview.h"

/******************************************************************************
*
*   Представление списка изображений
*
******************************************************************************/
class ImageSourcesView : public IColorSplitterView
{
public:
    ImageSourcesView();

    ImageSourcesView(const ImageSourcesView&)            = delete;
    ImageSourcesView(ImageSourcesView&&)                 = delete;

    ImageSourcesView& operator=(const ImageSourcesView&) = delete;
    ImageSourcesView& operator=(ImageSourcesView&&)      = delete;

    virtual QWidget *createWidget() const override;
    virtual void update(SplitterViewModel * model) override;

private:
    QHBoxLayout * createControls() const;

private:
    QPushButton * m_loadImagesButton;
    QRadioButton * m_showPath;
    QRadioButton * m_showName;
    QListView * m_imageSourcesView;
};

#endif // IMAGESOURCESVIEW_H
