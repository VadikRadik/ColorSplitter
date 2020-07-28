#ifndef RASTERIMAGE_H
#define RASTERIMAGE_H

#include <memory>

#include <QOpenGLTexture>

#include "OpenGLWidget/idrawable.h"

/******************************************************************************
*
*   Квад с текстурой
*
******************************************************************************/
class RasterImage : public IDrawable
{
public:
    RasterImage(const QImage &image, std::shared_ptr<QOpenGLShaderProgram> shader);

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override;

private:
    std::shared_ptr<QOpenGLShaderProgram> m_shaderProgram;
    QVector<GLfloat> m_vertices;
    QVector<GLfloat> m_textureCoords;
    std::unique_ptr<QOpenGLTexture> m_texture;

    QImage m_image;

    GLint m_attributeCoord2d;
    GLint m_attributeTextureCoords;
    GLint m_textureSampler;
    GLint m_projectionMatrix;
};

#endif // RASTERIMAGE_H
