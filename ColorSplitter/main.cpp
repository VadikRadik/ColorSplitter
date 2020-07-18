#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QImage>

#include "imagesourcesview.h"
#include "imageview.h"
#include "OpenGLWidget/openglwidget.h"
#include "DrawableObjects/rasterimage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<IColorSplitterView> imageSourcesView = std::make_shared<ImageSourcesView>();
    std::shared_ptr<IColorSplitterView> imageView = std::make_shared<ImageView>();
    std::shared_ptr<IColorSplitterView> colorDiagram = std::make_shared<ImageView>();

    MainWindow w;
    w.setImageSourcesView(imageSourcesView->createWidget());
    w.setImageView(imageView->createWidget());
    w.setColorDiagramView(colorDiagram->createWidget());
    w.setWidgets();

    w.showMaximized();

    return a.exec();
}
