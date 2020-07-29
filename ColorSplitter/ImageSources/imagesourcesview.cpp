#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

#include "imagesourcesview.h"
#include "uistrings.h"


/******************************************************************************
*   Конструктор
******************************************************************************/
ImageSourcesView::ImageSourcesView() // туду модель для листвью в параметры
    : m_loadImagesButton(new QPushButton(UI_STRINGS::LOAD_IMAGES_BUTTON_CAPTION))
    , m_showPath(new QRadioButton(UI_STRINGS::SHOW_IMAGE_PATH))
    , m_showName(new QRadioButton(UI_STRINGS::SHOW_FILE_NAME))
    , m_imageSourcesView(new QListView())
    , m_listModel(new ImageSourcesListModel())
{
    m_showPath->setChecked(true);
    m_imageSourcesView->setModel(m_listModel);
}


/******************************************************************************
*   Создание и передача виджета представления
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
*   Обновление представления по событию изменения модели
******************************************************************************/
void ImageSourcesView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{

}


/******************************************************************************
*   Создание элементов управления виджета представления
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
}
