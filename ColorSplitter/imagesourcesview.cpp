#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include "imagesourcesview.h"

ImageSourcesView::ImageSourcesView()
    : m_loadImagesButton(new QPushButton(LOAD_IMAGES_BUTTON_CAPTION))
    , m_showPath(new QRadioButton(SHOW_IMAGE_PATH))
    , m_showName(new QRadioButton(SHOW_FILE_NAME))
    , m_imageSourcesView(new QListView())
{
    m_showPath->setChecked(true);
}

QWidget * ImageSourcesView::createWidget() const
{
    QWidget * widget = new QWidget();

    QVBoxLayout * mainLayout = new QVBoxLayout();

    mainLayout->addLayout(createControls());
    mainLayout->addWidget(m_imageSourcesView);

    widget->setLayout(mainLayout);

    return widget;
}

QHBoxLayout *ImageSourcesView::createControls() const
{
    QHBoxLayout * viewControlsLayout = new QHBoxLayout();

    QGroupBox * showListWaysBox = new QGroupBox(WAY_TO_SHOW_CAPTION);
    QHBoxLayout * showListWaysLayout = new QHBoxLayout();

    showListWaysLayout->addWidget(m_showPath);
    showListWaysLayout->addWidget(m_showName);
    showListWaysBox->setLayout(showListWaysLayout);

    viewControlsLayout->addWidget(m_loadImagesButton);
    viewControlsLayout->addWidget(showListWaysBox);

    return viewControlsLayout;
}
