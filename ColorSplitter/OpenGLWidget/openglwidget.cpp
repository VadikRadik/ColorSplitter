#include "openglwidget.h"

#include <QDebug>

/******************************************************************************
*   Конструктор виджета
*   setFocusPolicy нужен для корректной работы keyPressEvent
******************************************************************************/
OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_scene()
{
    setFocusPolicy(Qt::StrongFocus);
}

OpenGLWidget::~OpenGLWidget()
{
    m_scene.flushObjects();
}


/******************************************************************************
*   Добавление рисуемого объекта в сцену
******************************************************************************/
void OpenGLWidget::addToScene(std::shared_ptr<IDrawable> obj)
{
    m_scene.addObject(obj);
}


/******************************************************************************
*   Инициализация контекста рисования
******************************************************************************/
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    m_scene.bindDrawContext(context());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


/******************************************************************************
*   Обработка события рисования виджета
******************************************************************************/
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_scene.draw();
}


/******************************************************************************
*   Обработка события изменения размера виджета
******************************************************************************/
void OpenGLWidget::resizeGL(int width, int height)
{
    m_scene.resizeView(width, height);
}


/******************************************************************************
*   Обработки событий ввода
******************************************************************************/

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_scene.wheelEvent(event);
    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_scene.mouseMoveEvent(event);
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_scene.mousePressEvent(event);
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    m_scene.keyPressEvent(event);
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_scene.keyReleaseEvent(event);
    update();
}
