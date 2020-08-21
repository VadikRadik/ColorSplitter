#include "abstractscene.h"
#include "ortho2dcamera.h"

/******************************************************************************
*   Constructor
******************************************************************************/
AbstractScene::AbstractScene(ICamera * camera)
    : m_camera(camera)
    , m_openGLContext(nullptr)
    , m_sceneObjects()
    , m_cotextSurface(nullptr)
{

}


/******************************************************************************
*   Memorizes a draw context
******************************************************************************/
void AbstractScene::bindDrawContext(QOpenGLContext *context)
{
    m_openGLContext = context;
    m_cotextSurface = context->surface();
}


/******************************************************************************
*   Draws scene objects
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
*   Handles resizing of the vieport
******************************************************************************/
void AbstractScene::resizeView(int width, int height)
{
    m_camera->resizeView(width,height);
}


/******************************************************************************
*   Adds an object to the scene
******************************************************************************/
void AbstractScene::addObject(std::shared_ptr<IDrawable> obj)
{
    makeCurrentContext();

    m_sceneObjects.push_back(obj);
}


/******************************************************************************
*   Turn on the draw context
******************************************************************************/
void AbstractScene::makeCurrentContext()
{
    m_openGLContext->makeCurrent(m_cotextSurface);
}


/******************************************************************************
*   Removes an object from the scene
******************************************************************************/
void AbstractScene::removeObject(std::shared_ptr<IDrawable> obj)
{
    makeCurrentContext();

    m_sceneObjects.remove(obj);
}


/******************************************************************************
*   Removes all objects from the scene
******************************************************************************/
void AbstractScene::flushObjects()
{
    makeCurrentContext();

    m_sceneObjects.clear();

    m_openGLContext->doneCurrent();
}


/******************************************************************************
*   Creates a shader in the scene context
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
*   Input handlers
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
