#include "rasterimage.h"

/******************************************************************************
*   Constructor.
*   Initializes quad's coordinates for the image
******************************************************************************/
RasterImage::RasterImage(const QImage &image, std::shared_ptr<QOpenGLShaderProgram> shader)
    : m_shaderProgram(shader)
    , m_attributeCoord2d(0)
    , m_attributeTextureCoords(0)
    , m_textureSampler(0)
    , m_projectionMatrix(0)
    , m_image(image)
    , m_texture(nullptr)
    , m_buffer()
    , m_bufferSize(0)
    , m_textureOffset(0)
{
    QVector<GLfloat> vertices;
    vertices <<   0.0f                    << 0.0f
             <<   0.0f                    << (float)image.height()
             <<   (float)image.width()    << (float)image.height()
             <<   (float)image.width()    << 0.0f;
    QVector<GLfloat> textureCoords;
    textureCoords <<  0.0f << 0.0f
                  <<  0.0f << 1.0f
                  <<  1.0f << 1.0f
                  <<  1.0f << 0.0f;

    m_bufferSize = vertices.size() / VERTEX_DIMENSIONS;
    createBuffer(vertices,textureCoords);

    setShader(shader);
}

RasterImage::~RasterImage()
{
    m_buffer.destroy();
}


/******************************************************************************
*   Draws the textured quad
******************************************************************************/
void RasterImage::draw(QOpenGLFunctions * oglFunctions, const DrawParameters &drawParams)
{
    if ( !m_shaderProgram->bind() || !m_buffer.isCreated() ) {
        return;
    }

    m_buffer.bind();

    m_shaderProgram->setAttributeBuffer(m_attributeCoord2d, GL_FLOAT, 0, VERTEX_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeCoord2d);
    m_shaderProgram->setAttributeBuffer(m_attributeTextureCoords, GL_FLOAT, m_textureOffset, VERTEX_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeTextureCoords);

    m_buffer.release();

    m_texture->bind();

    m_shaderProgram->setUniformValue( m_textureSampler, 0 );
    m_shaderProgram->setUniformValue( m_projectionMatrix, drawParams.projectionViewMatrix );

    oglFunctions->glDrawArrays(GL_QUADS,0,m_bufferSize);

    m_shaderProgram->disableAttributeArray( m_attributeCoord2d );
    m_shaderProgram->disableAttributeArray( m_attributeTextureCoords );

    m_texture->release();
    m_shaderProgram->release();
}


/******************************************************************************
*   Changes the shader
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


/******************************************************************************
*   Creates a buffer for the quad
******************************************************************************/
void RasterImage::createBuffer(const QVector<GLfloat> &vertices, const QVector<GLfloat> &textuerCoordinates)
{
    m_buffer.create();
    m_buffer.bind();

    int verticesPartSize = vertices.size() * sizeof(GLfloat);
    int texturePartSize = textuerCoordinates.size() * sizeof(GLfloat);
    m_buffer.allocate(verticesPartSize + texturePartSize);

    int offset = 0;
    m_buffer.write(offset, vertices.data(),verticesPartSize);
    offset += verticesPartSize;
    m_textureOffset = offset;
    m_buffer.write(offset, textuerCoordinates.data(),texturePartSize);

    m_buffer.release();
}
