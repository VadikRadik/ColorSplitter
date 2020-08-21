#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "OpenGLWidget/idrawable.h"
#include <QColor>

/******************************************************************************
*
*   The scene's background
*
******************************************************************************/
class Background : public IDrawable
{
public:
    Background(const QColor & color);

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override {}

private:
    QColor m_color;
};

#endif // BACKGROUND_H
