#include "openglwidget.h"

/******************************************************************************
*   Constructor
******************************************************************************/
OpenGLWidget::OpenGLWidget(std::shared_ptr<AbstractScene> scene, std::shared_ptr<IWidgetInputHandler> controller, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_scene(scene)
    , m_controller(controller)
{
    setFocusPolicy(Qt::StrongFocus); // for keyPressEvent
}


/******************************************************************************
*   The scene's drawable objects must be removed in correct context
******************************************************************************/
OpenGLWidget::~OpenGLWidget()
{
    m_scene->flushObjects();
}


/******************************************************************************
*   The draw context initialization
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
*   The paint event handler
******************************************************************************/
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_scene->draw();
}


/******************************************************************************
*   The resize event handler
******************************************************************************/
void OpenGLWidget::resizeGL(int width, int height)
{
    m_scene->resizeView(width, height);
}


/******************************************************************************
*   The input handlers
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
