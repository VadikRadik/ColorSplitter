#include "mainwindow.h"
#include <QApplication>
#include <memory>

#include "imagesourcesview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<IColorSplitterView> imageSourcesView = std::make_shared<ImageSourcesView>();

    MainWindow w;
    w.setImageSourcesView(imageSourcesView->createWidget());
    w.show();

    return a.exec();
}
