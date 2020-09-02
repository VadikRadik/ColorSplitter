#include <memory>

#include <QApplication>

#include "mainwindow.h"
#include "ImageSources/imagesourcesview.h"
#include "ImageSources/imagesourcescontroller.h"
#include "Image/imageview.h"
#include "Image/imagecontroller.h"
#include "ColorDiagram/colordiagramview.h"
#include "ColorDiagram/colordiagramcontroller.h"
#include "colorsplittermodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    ColorSplitterModel model;

    std::shared_ptr<ImageSourcesController> imageSourcesController = std::make_shared<ImageSourcesController>(model);
    std::shared_ptr<ColorDiagramController> colorDiagramController = std::make_shared<ColorDiagramController>(model);
    std::shared_ptr<ImageController> imageController = std::make_shared<ImageController>(model);

    std::shared_ptr<IColorSplitterView> imageSourcesView = std::make_shared<ImageSourcesView>(imageSourcesController);
    std::shared_ptr<IColorSplitterView> imageView = std::make_shared<ImageView>(imageController);
    std::shared_ptr<IColorSplitterView> colorDiagram = std::make_shared<ColorDiagramView>(colorDiagramController);

    model.subscribeView(imageSourcesView);
    model.subscribeView(colorDiagram);
    model.subscribeView(imageView);

    MainWindow w;

    w.setImageSourcesView(imageSourcesView->createWidget());
    w.setColorDiagramView(colorDiagram->createWidget());
    w.setImageView(imageView->createWidget());
    w.setWidgets();

    w.showMaximized();

    return a.exec();
}
