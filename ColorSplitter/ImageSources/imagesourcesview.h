#ifndef IMAGESOURCESVIEW_H
#define IMAGESOURCESVIEW_H

#include <QListView>
#include <QPushButton>
#include <QString>
#include <QRadioButton>
#include <QHBoxLayout>

#include "icolorsplitterview.h"
#include "imagesourceslistmodel.h"
#include "imagesourcescontroller.h"

/******************************************************************************
*
*   Представление списка изображений
*
******************************************************************************/
class ImageSourcesView : public IColorSplitterView
{
public:
    ImageSourcesView(std::shared_ptr<ImageSourcesController> controller);

    ImageSourcesView(const ImageSourcesView&)            = delete;
    ImageSourcesView(ImageSourcesView&&)                 = delete;

    ImageSourcesView& operator=(const ImageSourcesView&) = delete;
    ImageSourcesView& operator=(ImageSourcesView&&)      = delete;

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    QHBoxLayout * createControls() const;
    void createLogic(QWidget * widget) const;

private:
    QPushButton * m_loadImagesButton;
    QRadioButton * m_showPath;
    QRadioButton * m_showName;
    QListView * m_imageSourcesView;
    ImageSourcesListModel * m_listModel;
    std::shared_ptr<ImageSourcesController> m_controller;
};

#endif // IMAGESOURCESVIEW_H
