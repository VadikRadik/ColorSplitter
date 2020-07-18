#include "scene.h"

#include "ortho2dcamera.h"


/******************************************************************************
*   Конструктор
******************************************************************************/
Scene::Scene()
    : m_camera(new Ortho2DCamera())
    , m_openGLContext(nullptr)
    , m_sceneObjects()
{

}


/******************************************************************************
*   Запоминание контекста рисования
******************************************************************************/
void Scene::bindDrawContext(QOpenGLContext *context)
{
    m_openGLContext = context;
}


/******************************************************************************
*   Рисование объектов сцены
******************************************************************************/
void Scene::draw()
{
    DrawParameters params;
    params.pvm = m_camera->projectionMatrix() * m_camera->viewMatrix();

    for (auto & obj : m_sceneObjects) {
        obj->draw(m_openGLContext->functions(), params);
    }
}


/******************************************************************************
*   Обработка изменение размеров окна
******************************************************************************/
void Scene::resizeView(int width, int height)
{
    m_camera->resizeView(width,height);
}


/******************************************************************************
*   Добавление объекта в сцену
******************************************************************************/
void Scene::addObject(std::shared_ptr<IDrawable> obj)
{
    m_openGLContext->makeCurrent(m_openGLContext->surface());

    obj->initialize();
    m_sceneObjects.push_back(obj);

    m_openGLContext->doneCurrent();
}


/******************************************************************************
*   Удаление объекта из сцены
******************************************************************************/
void Scene::removeObject(std::shared_ptr<IDrawable> obj)
{
    m_openGLContext->makeCurrent(m_openGLContext->surface());

    m_sceneObjects.remove(obj);

    m_openGLContext->doneCurrent();
}


/******************************************************************************
*   Очистка сцены от объектов
******************************************************************************/
void Scene::flushObjects()
{
    m_openGLContext->makeCurrent(m_openGLContext->surface());

    m_sceneObjects.clear();

    m_openGLContext->doneCurrent();
}


/******************************************************************************
*   Обработка событий ввода
******************************************************************************/

void Scene::wheelEvent(QWheelEvent *event)
{
    m_camera->wheelEvent(event);
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    m_camera->mouseMoveEvent(event);
}

void Scene::mousePressEvent(QMouseEvent *event)
{
    m_camera->mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    m_camera->keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    m_camera->keyReleaseEvent(event);
}
