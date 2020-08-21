#include "mesh.h"


Mesh::Mesh(std::shared_ptr<QOpenGLShaderProgram> shader, GLenum drawMode)
    : m_shaderProgram(shader)
    , m_vertices()
    , m_normals()
    , m_colors()
    , m_attributeCoord3d(0)
    , m_attributeNormals(0)
    , m_attributeColors(0)
    , m_uniformLightDir(0)
    , m_uniformPvm(0)
    , m_drawMode(drawMode)
    , m_buffer()
    , m_modelMatrix()
    , m_bufferSize(0)
    , m_colorsOffset(0)
    , m_normalsOffset(0)
{
    bindShaderAttributes();
}

Mesh::~Mesh()
{
    m_buffer.destroy();
}


/******************************************************************************
*   Draws the mesh
******************************************************************************/
void Mesh::draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams)
{
    if ( !m_shaderProgram->bind() || !m_buffer.isCreated() ) {
        return;
    }

    m_buffer.bind();

    m_shaderProgram->setAttributeBuffer(m_attributeCoord3d, GL_FLOAT, 0, VERTEX_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeCoord3d);
    m_shaderProgram->setAttributeBuffer(m_attributeNormals, GL_FLOAT, m_normalsOffset, VERTEX_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeNormals);
    m_shaderProgram->setAttributeBuffer(m_attributeColors, GL_FLOAT, m_colorsOffset, COLOR_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeColors);

    m_buffer.release();

    m_shaderProgram->setUniformValue( m_uniformLightDir, drawParams.lightDirection );
    m_shaderProgram->setUniformValue( m_uniformPvm, drawParams.projectionViewMatrix * m_modelMatrix);

    oglFunctions->glDrawArrays(m_drawMode,0,m_bufferSize);

    m_shaderProgram->disableAttributeArray(m_attributeColors);
    m_shaderProgram->disableAttributeArray(m_attributeNormals);
    m_shaderProgram->disableAttributeArray(m_attributeCoord3d);

    m_shaderProgram->release();
}


/******************************************************************************
*   Changes the shader
******************************************************************************/
void Mesh::setShader(std::shared_ptr<QOpenGLShaderProgram> shader)
{
    m_shaderProgram = shader;

    bindShaderAttributes();
}


/******************************************************************************
*   Moves the vertices coordinates to the mesh
*   Memorizes vertices count
******************************************************************************/
void Mesh::setVertices(std::vector<GLfloat> &vertices)
{
    m_vertices = std::move(vertices);
    m_bufferSize = m_vertices.size() / VERTEX_DIMENSIONS;
}


/******************************************************************************
*   Moves the vertices normals to the mesh
******************************************************************************/
void Mesh::setNormals(std::vector<GLfloat> &normals)
{
    m_normals = std::move(normals);
}

/******************************************************************************
*   Moves the vertices colors to the mesh
******************************************************************************/
void Mesh::setColors(std::vector<GLfloat> &colors)
{
    m_colors = std::move(colors);
}


/******************************************************************************
*   Creates a buffer for the mesh
******************************************************************************/
void Mesh::createBuffer()
{
    m_buffer.create();
    m_buffer.bind();

    int verticesPartSize = m_vertices.size() * sizeof(GLfloat);
    int normalsPartSize = m_normals.size() * sizeof(GLfloat);
    int colorsPartSize = m_colors.size() * sizeof(GLfloat);
    m_buffer.allocate(verticesPartSize + normalsPartSize + colorsPartSize);

    int offset = 0;
    m_buffer.write(offset, m_vertices.data(),verticesPartSize);
    offset += verticesPartSize;
    m_normalsOffset = offset;
    m_buffer.write(offset, m_normals.data(),normalsPartSize);
    offset += normalsPartSize;
    m_colorsOffset = offset;
    m_buffer.write(offset, m_colors.data(),colorsPartSize);

    m_buffer.release();

    m_vertices.clear();
    m_normals.clear();
    m_colors.clear();
    m_vertices.shrink_to_fit();
    m_normals.shrink_to_fit();
    m_colors.shrink_to_fit();
}


/******************************************************************************
*   Binds shader's attributes
******************************************************************************/
void Mesh::bindShaderAttributes()
{
    m_uniformLightDir = m_shaderProgram->uniformLocation( SHADER_VARIABLES::UF_LIGHT_DIRECTION );
    m_uniformPvm = m_shaderProgram->uniformLocation( SHADER_VARIABLES::UF_PVM_MATRIX );

    m_attributeCoord3d = m_shaderProgram->attributeLocation(SHADER_VARIABLES::ATR_COORD_3D);
    m_attributeNormals = m_shaderProgram->attributeLocation(SHADER_VARIABLES::ATR_NORMAL);
    m_attributeColors = m_shaderProgram->attributeLocation(SHADER_VARIABLES::ATR_COLOR);
}
