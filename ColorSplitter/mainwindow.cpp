#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(100,100,666,333);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setImageSourcesView(QWidget *view)
{
    setCentralWidget(view);
}
