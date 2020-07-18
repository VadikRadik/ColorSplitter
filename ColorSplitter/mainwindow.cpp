#include "mainwindow.h"

#include <QVBoxLayout>


/******************************************************************************
*   Конструктор
*   Инициализация размеров окна по умолчанию
******************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_verticalSplitter(new QSplitter(Qt::Horizontal))
    , m_horizontalSplitter(new QSplitter(Qt::Vertical))
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
    m_horizontalSplitter->addWidget(view);
}


/******************************************************************************
*   Добавление представления цветовой диаграммы
******************************************************************************/
void MainWindow::setColorDiagramView(QWidget *view)
{
    m_horizontalSplitter->addWidget(view);
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

    m_horizontalSplitter->setStretchFactor(0,3);
    m_horizontalSplitter->setStretchFactor(1,2);
    m_horizontalSplitter->setGeometry(0,0,100,100);

    m_verticalSplitter->addWidget(m_imageSourceView);
    m_verticalSplitter->addWidget(m_horizontalSplitter);
    m_verticalSplitter->setStretchFactor(0,1);
    m_verticalSplitter->setStretchFactor(1,10);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_verticalSplitter);
    mainWidget->setLayout(mainLayout);

    return mainWidget;
}
