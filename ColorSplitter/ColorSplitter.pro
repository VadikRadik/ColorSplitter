#-------------------------------------------------
#
# Project created by QtCreator 2020-07-08T15:20:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorSplitter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    ImageSources/imagesourcesview.cpp \
    OpenGLWidget/openglwidget.cpp \
    DrawableObjects/rasterimage.cpp \
    OpenGLWidget/ortho2dcamera.cpp \
    Image/imageview.cpp \
    OpenGLWidget/centred3deulercamera.cpp \
    ColorDiagram/colordiagramview.cpp \
    DrawableObjects/mesh.cpp \
    OpenGLWidget/abstractscene.cpp \
    ColorDiagram/colordiagramscene.cpp \
    Image/imagescene.cpp \
    DrawableObjects/background.cpp \
    ColorDiagram/meshbuilder.cpp \
    ColorDiagram/imeshpattern.cpp \
    DrawableObjects/meshpack.cpp \
    colorsplittermodel.cpp \
    ImageSources/imagesourceslistmodel.cpp

HEADERS  += mainwindow.h \
    icolorsplitterview.h \
    ImageSources/imagesourcesview.h \
    uistrings.h \
    OpenGLWidget/openglwidget.h \
    OpenGLWidget/idrawable.h \
    DrawableObjects/rasterimage.h \
    OpenGLWidget/icamera.h \
    OpenGLWidget/ortho2dcamera.h \
    Image/imageview.h \
    OpenGLWidget/centred3deulercamera.h \
    ColorDiagram/colordiagramview.h \
    DrawableObjects/mesh.h \
    OpenGLWidget/abstractscene.h \
    ColorDiagram/colordiagramscene.h \
    Image/imagescene.h \
    DrawableObjects/background.h \
    ColorDiagram/meshbuilder.h \
    ColorDiagram/imeshpattern.h \
    DrawableObjects/meshpack.h \
    colorsplittermodel.h \
    emodelupdates.h \
    ImageSources/imagesourceslistmodel.h

RESOURCES += \
    DrawableObjects/shaders.qrc
