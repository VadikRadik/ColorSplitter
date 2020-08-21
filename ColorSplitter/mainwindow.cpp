#include "mainwindow.h"

#include <QVBoxLayout>

/******************************************************************************
*   Main window constructor
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
*   Adds the images list widget to the main window
******************************************************************************/
void MainWindow::setImageSourcesView(QWidget *view)
{
    m_imageSourceView = view;
}


/******************************************************************************
*   Adds the image widget to the main window
******************************************************************************/
void MainWindow::setImageView(QWidget *view)
{
    m_openglViewsSplitter->addWidget(view);
}


/******************************************************************************
*   Adds the color diagram widget to the main window
******************************************************************************/
void MainWindow::setColorDiagramView(QWidget *view)
{
    m_openglViewsSplitter->addWidget(view);
}


/******************************************************************************
*   Adds all widgets to the main window
******************************************************************************/
void MainWindow::setWidgets()
{
    setCentralWidget(createCentralWidget());
}


/******************************************************************************
*   Sets widget's geometry
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
