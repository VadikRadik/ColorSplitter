#include "abstractscene.h"

#include "ortho2dcamera.h"


/******************************************************************************
*   Конструктор
******************************************************************************/
AbstractScene::AbstractScene(ICamera * camera)
    : m_camera(camera)
    , m_openGLContext(nullptr)
    , m_cotextSurface(nullptr)
    , m_sceneObjects()
{

}


/******************************************************************************
*   Запоминание контекста рисования
******************************************************************************/
void AbstractScene::bindDrawContext(QOpenGLContext *context)
{
    m_openGLContext = context;
    m_cotextSurface = context->surface();
}

//void AbstractScene::setCamera(ICamera *camera)
//{
//    m_camera.reset(camera);
//}


/******************************************************************************
*   Рисование объектов сцены
******************************************************************************/
void AbstractScene::draw()
{
    DrawParameters params;
    params.projectionViewMatrix = m_camera->projectionMatrix() * m_camera->viewMatrix();
    params.lightDirection = m_camera->viewDirection();

    for (auto & obj : m_sceneObjects) {
        obj->draw(m_openGLContext->functions(), params);
    }
}


/******************************************************************************
*   Обработка изменение размеров окна
******************************************************************************/
void AbstractScene::resizeView(int width, int height)
{
    m_camera->resizeView(width,height);
}


/******************************************************************************
*   Добавление объекта в сцену
******************************************************************************/
void AbstractScene::addObject(std::shared_ptr<IDrawable> obj)
{
    makeCurrentContext();

    m_sceneObjects.push_back(obj);
}


/******************************************************************************
*   Включение контекста
******************************************************************************/
void AbstractScene::makeCurrentContext()
{
    m_openGLContext->makeCurrent(m_cotextSurface);
}


/******************************************************************************
*   Удаление объекта из сцены
******************************************************************************/
void AbstractScene::removeObject(std::shared_ptr<IDrawable> obj)
{
    makeCurrentContext();

    m_sceneObjects.remove(obj);
}


/******************************************************************************
*   Очистка сцены от объектов
******************************************************************************/
void AbstractScene::flushObjects()
{
    makeCurrentContext();

    m_sceneObjects.clear();

    m_openGLContext->doneCurrent();
}


/******************************************************************************
*   Создание шейдера в контексте
******************************************************************************/
std::shared_ptr<QOpenGLShaderProgram> AbstractScene::createShader(const QString &vertexShaderPath,
                                                            const QString &fragmentShaderPath,
                                                            const QString &geometryShaderPath)
{
    std::shared_ptr<QOpenGLShaderProgram> shaderProgram = std::make_shared<QOpenGLShaderProgram>();

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    if ( !vShader.compileSourceFile( vertexShaderPath ))
        qWarning() << "Vertex shader compile error\n";

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    if ( !fShader.compileSourceFile( fragmentShaderPath ))
        qWarning() << "Fragment shader compile error\n";

    shaderProgram->addShader( &vShader );
    shaderProgram->addShader( &fShader );

    if (!geometryShaderPath.isEmpty()) {
        QOpenGLShader gShader( QOpenGLShader::Geometry );
        if ( !gShader.compileSourceFile( geometryShaderPath ))
            qWarning() << "Geometry shader compile error\n";
        shaderProgram->addShader( &gShader );
    }

    if ( !shaderProgram->link() ) {
        qWarning( "Error: unable to link a shader program." );
    }

    return shaderProgram;
}


/******************************************************************************
*   Обработка событий ввода
******************************************************************************/

void AbstractScene::wheelEvent(QWheelEvent *event)
{
    m_camera->wheelEvent(event);
}

void AbstractScene::mouseMoveEvent(QMouseEvent *event)
{
    m_camera->mouseMoveEvent(event);
}

void AbstractScene::mousePressEvent(QMouseEvent *event)
{
    m_camera->mousePressEvent(event);
}

void AbstractScene::keyPressEvent(QKeyEvent *event)
{
    m_camera->keyPressEvent(event);
}

void AbstractScene::keyReleaseEvent(QKeyEvent *event)
{
    m_camera->keyReleaseEvent(event);
}

void AbstractScene::mouseReleaseEvent(QMouseEvent *event)
{
    m_camera->mouseReleaseEvent(event);
}
