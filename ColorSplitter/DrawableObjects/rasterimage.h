#ifndef RASTERIMAGE_H
#define RASTERIMAGE_H

#include <memory>

#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include "OpenGLWidget/idrawable.h"

/******************************************************************************
*
*   A textured quad
*
******************************************************************************/
class RasterImage : public IDrawable
{
public:
    RasterImage(const QImage &image, std::shared_ptr<QOpenGLShaderProgram> shader);
    ~RasterImage();

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override;

private:
    void createBuffer(const QVector<GLfloat> & vertices, const QVector<GLfloat> & textuerCoordinates);

private:
    std::shared_ptr<QOpenGLShaderProgram> m_shaderProgram;
    std::unique_ptr<QOpenGLTexture> m_texture;

    QImage m_image;

    GLint m_attributeCoord2d;
    GLint m_attributeTextureCoords;
    GLint m_textureSampler;
    GLint m_projectionMatrix;

    QOpenGLBuffer m_buffer;

    int m_bufferSize;
    int m_textureOffset;

    static const int VERTEX_DIMENSIONS = 2;
};

#endif // RASTERIMAGE_H
