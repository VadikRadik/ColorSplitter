#include "mainwindow.h"

#include <QVBoxLayout>


/******************************************************************************
*   Конструктор
*   Инициализация размеров окна по умолчанию
******************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_imageSourceSplitter(new QSplitter(Qt::Horizontal))
    , m_openglViewsSplitter(new QSplitter(Qt::Vertical))
    , m_imageSourceView(nullptr)
{
    setGeometry(DEFAULT_MAIN_WINDOW_GEOMETRY);
}

MainWindow::~MainWindow()
{

}


/******************************************************************************
*   Добавление представления списка изображений
******************************************************************************/
void MainWindow::setImageSourcesView(QWidget *view)
{
    m_imageSourceView = view;
}


/******************************************************************************
*   Добавление представления изображеня
******************************************************************************/
void MainWindow::setImageView(QWidget *view)
{
    m_openglViewsSplitter->addWidget(view);
}


/******************************************************************************
*   Добавление представления цветовой диаграммы
******************************************************************************/
void MainWindow::setColorDiagramView(QWidget *view)
{
    m_openglViewsSplitter->addWidget(view);
}


/******************************************************************************
*   Добавление представлений в окно
******************************************************************************/
void MainWindow::setWidgets()
{
    setCentralWidget(createCentralWidget());
}


/******************************************************************************
*   Создание окна
******************************************************************************/
QWidget *MainWindow::createCentralWidget()
{
    QWidget * mainWidget = new QWidget();

    m_openglViewsSplitter->setStretchFactor(0,5);
    m_openglViewsSplitter->setStretchFactor(1,1);

    m_imageSourceSplitter->addWidget(m_imageSourceView);
    m_imageSourceSplitter->addWidget(m_openglViewsSplitter);
    m_imageSourceSplitter->setStretchFactor(0,1);
    m_imageSourceSplitter->setStretchFactor(1,10);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_imageSourceSplitter);
    mainWidget->setLayout(mainLayout);

    return mainWidget;
}
