#include "openglwidget.h"

#include <QDebug>

/******************************************************************************
*   Конструктор виджета
*   setFocusPolicy нужен для корректной работы keyPressEvent
******************************************************************************/
OpenGLWidget::OpenGLWidget(std::shared_ptr<AbstractScene> scene, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_scene(scene)
{
    setFocusPolicy(Qt::StrongFocus);
}


/******************************************************************************
*   Объектам сцены с текстурами необходимо удаляться в этом деструкторе
******************************************************************************/
OpenGLWidget::~OpenGLWidget()
{
    m_scene->flushObjects();
}


/******************************************************************************
*   Инициализация контекста рисования
******************************************************************************/
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_scene->bindDrawContext(context());
    m_scene->initialize();
}


/******************************************************************************
*   Обработка события рисования виджета
******************************************************************************/
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_scene->draw();
}


/******************************************************************************
*   Обработка события изменения размера виджета
******************************************************************************/
void OpenGLWidget::resizeGL(int width, int height)
{
    m_scene->resizeView(width, height);
}


/******************************************************************************
*   Обработки событий ввода
******************************************************************************/

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_scene->wheelEvent(event);
    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_scene->mouseMoveEvent(event);
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_scene->mousePressEvent(event);
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    m_scene->keyPressEvent(event);
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_scene->keyReleaseEvent(event);
    update();
}
