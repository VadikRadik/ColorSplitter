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
*   View of images list. Creates the images list widget
*
******************************************************************************/
class ImageSourcesView : public IColorSplitterView
{
public:
    ImageSourcesView(std::shared_ptr<ImageSourcesController> controller);

    virtual QWidget *createWidget() const override;
    virtual void update(const ColorSplitterModel * model, EModelUpdates stateChange) override;

private:
    QHBoxLayout * createControls() const;
    void createLogic(QWidget * widget) const;

private:
    std::shared_ptr<ImageSourcesController> m_controller;
    QPushButton * m_loadImagesButton;
    QRadioButton * m_showPath;
    QRadioButton * m_showName;
    QListView * m_imageSourcesView;
    ImageSourcesListModel * m_listModel;
};

#endif // IMAGESOURCESVIEW_H
