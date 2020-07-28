#include "rasterimage.h"

/******************************************************************************
*   Конструктор.
*   Инициализация координат квада под изображение
******************************************************************************/
RasterImage::RasterImage(const QImage &image, std::shared_ptr<QOpenGLShaderProgram> shader)
    : m_shaderProgram(shader)
    , m_vertices()
    , m_textureCoords()
    , m_attributeCoord2d(0)
    , m_attributeTextureCoords(0)
    , m_textureSampler(0)
    , m_projectionMatrix(0)
    , m_image(image)
    , m_texture(nullptr)
{
    m_vertices <<   0.0f                    << 0.0f
               <<   (float)image.width()    << 0.0f
               <<   (float)image.width()    << (float)image.height()
               <<   0.0f                    << (float)image.height();
    m_textureCoords <<  0.0f << 0.0f
                    <<  1.0f << 0.0f
                    <<  1.0f << 1.0f
                    <<  0.0f << 1.0f;

    setShader(shader);
}


/******************************************************************************
*   Рисование квада с текстурой
******************************************************************************/
void RasterImage::draw(QOpenGLFunctions * oglFunctions, const DrawParameters &drawParams)
{
    if ( !m_shaderProgram->bind() )
        return;

    m_texture->bind();
    m_shaderProgram->setAttributeArray( m_attributeTextureCoords, m_textureCoords.data(), 2 );
    m_shaderProgram->setUniformValue( m_textureSampler, 0 );

    m_shaderProgram->setUniformValue( m_projectionMatrix, drawParams.projectionViewMatrix );

    m_shaderProgram->setAttributeArray( m_attributeCoord2d, m_vertices.data(), 2 );

    m_shaderProgram->enableAttributeArray( m_attributeCoord2d );
    m_shaderProgram->enableAttributeArray( m_attributeTextureCoords );

    oglFunctions->glDrawArrays(GL_QUADS,0,4);

    m_shaderProgram->disableAttributeArray( m_attributeCoord2d );
    m_shaderProgram->disableAttributeArray( m_attributeTextureCoords );

    m_shaderProgram->release();
}


/******************************************************************************
*   Установка шейдера для квада с текстурой
******************************************************************************/
void RasterImage::setShader(std::shared_ptr<QOpenGLShaderProgram> shader)
{
    m_shaderProgram = shader;

    m_attributeCoord2d = m_shaderProgram->attributeLocation( SHADER_VARIABLES::ATR_COORD_2D );
    m_attributeTextureCoords = m_shaderProgram->attributeLocation( SHADER_VARIABLES::ATR_TEXTURE_COORDS );
    m_textureSampler = m_shaderProgram->uniformLocation( SHADER_VARIABLES::UF_TEXTURE );
    m_projectionMatrix = m_shaderProgram->uniformLocation( SHADER_VARIABLES::UF_PVM_MATRIX );

    m_texture.reset(new QOpenGLTexture( m_image ));
    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
}
