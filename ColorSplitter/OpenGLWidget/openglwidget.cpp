#include "openglwidget.h"

#include <QDebug>
#include <QTime>

/******************************************************************************
*   Конструктор виджета
*   setFocusPolicy нужен для корректной работы keyPressEvent
******************************************************************************/
OpenGLWidget::OpenGLWidget(std::shared_ptr<AbstractScene> scene, std::shared_ptr<IWidgetImputHandler> controller, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_scene(scene)
    , m_controller(controller)
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
    glEnable(GL_CULL_FACE);

    glLineWidth(2.0f);
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
    if (m_controller != nullptr)
        m_controller->wheelEvent(event);
    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_scene->mouseMoveEvent(event);
    if (m_controller != nullptr)
        m_controller->mouseMoveEvent(event);
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_scene->mousePressEvent(event);
    if (m_controller != nullptr)
        m_controller->mousePressEvent(event);
    update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_scene->mouseReleaseEvent(event);
    if (m_controller != nullptr)
        m_controller->mouseReleaseEvent(event);
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    m_scene->keyPressEvent(event);
    if (m_controller != nullptr)
        m_controller->keyPressEvent(event);
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_scene->keyReleaseEvent(event);
    if (m_controller != nullptr)
        m_controller->keyReleaseEvent(event);
    update();
}
