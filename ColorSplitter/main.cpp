#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QImage>

#include "ImageSources/imagesourcesview.h"
#include "Image/imageview.h"
#include "ColorDiagram/colordiagramview.h"
#include "OpenGLWidget/openglwidget.h"
#include "DrawableObjects/rasterimage.h"
#include "colorsplittermodel.h"
#include "ImageSources/imagesourcescontroller.h"
#include "ColorDiagram/colordiagramcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    ColorSplitterModel model;

    std::shared_ptr<ImageSourcesController> imageSourcesController = std::make_shared<ImageSourcesController>(model);
    std::shared_ptr<ColorDiagramController> colorDiagramController = std::make_shared<ColorDiagramController>(model);

    std::shared_ptr<IColorSplitterView> imageSourcesView = std::make_shared<ImageSourcesView>(imageSourcesController);
    std::shared_ptr<IColorSplitterView> imageView = std::make_shared<ImageView>();
    std::shared_ptr<IColorSplitterView> colorDiagram = std::make_shared<ColorDiagramView>(colorDiagramController);

    model.subscribeView(imageSourcesView);
    model.subscribeView(imageView);
    model.subscribeView(colorDiagram);

    MainWindow w;
    w.setImageSourcesView(imageSourcesView->createWidget());
    w.setColorDiagramView(colorDiagram->createWidget());
    w.setImageView(imageView->createWidget());
    w.setWidgets();
    w.showMaximized();

    return a.exec();
}
