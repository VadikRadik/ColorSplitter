#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

/******************************************************************************
*
*   Главное окно
*
******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setImageSourcesView    (QWidget * view);
    void setImageView           (QWidget * view);
    void setColorDiagramView    (QWidget * view);

    void setWidgets();

private:
    QWidget * createCentralWidget();

private:
    QWidget * m_imageSourceView;
    QSplitter * m_imageSourceSplitter;
    QSplitter * m_openglViewsSplitter;

    const QRect DEFAULT_MAIN_WINDOW_GEOMETRY = QRect(QPoint(100,100),QPoint(999,666));
};

#endif // MAINWINDOW_H
