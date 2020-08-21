#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

#include "imagesourcesview.h"
#include "uistrings.h"

/******************************************************************************
*   Constructor
******************************************************************************/
ImageSourcesView::ImageSourcesView(std::shared_ptr<ImageSourcesController> controller)
    : m_controller(controller)
    , m_loadImagesButton(new QPushButton(UI_STRINGS::LOAD_IMAGES_BUTTON_CAPTION))
    , m_showPath(new QRadioButton(UI_STRINGS::SHOW_IMAGE_PATH))
    , m_showName(new QRadioButton(UI_STRINGS::SHOW_FILE_NAME))
    , m_imageSourcesView(new QListView())
    , m_listModel(new ImageSourcesListModel())
{
    m_showPath->setChecked(true);
    m_imageSourcesView->setModel(m_listModel);
}


/******************************************************************************
*   Creates the widget of the images list
******************************************************************************/
QWidget * ImageSourcesView::createWidget() const
{
    QWidget * widget = new QWidget();

    QVBoxLayout * mainLayout = new QVBoxLayout();

    mainLayout->addLayout(createControls());
    mainLayout->addWidget(m_imageSourcesView);

    widget->setLayout(mainLayout);

    createLogic(widget);

    return widget;
}


/******************************************************************************
*   Updates the view by changing of a model state
******************************************************************************/
void ImageSourcesView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{

}


/******************************************************************************
*   Creates controls
******************************************************************************/
QHBoxLayout *ImageSourcesView::createControls() const
{
    QHBoxLayout * viewControlsLayout = new QHBoxLayout();

    QGroupBox * showListWaysBox = new QGroupBox(UI_STRINGS::WAY_TO_SHOW_CAPTION);
    QHBoxLayout * showListWaysLayout = new QHBoxLayout();

    showListWaysLayout->addWidget(m_showPath);
    showListWaysLayout->addWidget(m_showName);
    showListWaysBox->setLayout(showListWaysLayout);

    viewControlsLayout->addWidget(m_loadImagesButton);
    viewControlsLayout->addWidget(showListWaysBox);

    return viewControlsLayout;
}


/******************************************************************************
*   Creates controls event handlers
******************************************************************************/
void ImageSourcesView::createLogic(QWidget *widget) const
{
    widget->connect(m_loadImagesButton,&QPushButton::clicked,[=](){
        QStringList list = QFileDialog::getOpenFileNames(widget, UI_STRINGS::OPEN_FILES, "", "*.png *.bmp *.jpeg *.jpg");
        if (!list.isEmpty()){
            m_listModel->addImages(list);
        }
    });

    widget->connect(m_showPath,&QRadioButton::pressed,[=](){
        m_listModel->setDisplayRegime(EDisplayRegime::FULL_PATH);
    });
    widget->connect(m_showName,&QRadioButton::pressed,[=](){
        m_listModel->setDisplayRegime(EDisplayRegime::FILE_NAME);
    });

    widget->connect(m_imageSourcesView->selectionModel(),&QItemSelectionModel::currentChanged,[=](QModelIndex index, QModelIndex previousIndex) {
        m_controller->setImage(m_listModel->data(index,Qt::UserRole).toString());
    });
}
