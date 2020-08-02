#include "lineframe.h"

LineFrame::LineFrame(std::shared_ptr<QOpenGLShaderProgram> shader, QPointF startPosition)
    : m_shaderProgram(shader)
    , m_vertices()
    , m_colors()
    , m_attributeCoord2d(0)
    , m_attributeColors(0)
    , m_uniformPvm(0)
    , m_buffer()
    , m_bufferSize(0)
    , m_colorsOffset(0)
    , m_movablePoint()
{
    m_vertices = {
        startPosition.x(), startPosition.y(),
        startPosition.x(), startPosition.y(),
        startPosition.x(), startPosition.y(),
        startPosition.x(), startPosition.y()
    };
    calcInnerLoops();

    m_colors = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    m_movablePoint = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_bufferSize = m_vertices.size() / VERTEX_DIMENSIONS;
    createBuffer();
    bindShaderAttributes();
}

LineFrame::~LineFrame()
{
    m_buffer.destroy();
}


/******************************************************************************
*   Отрисовка рамки
******************************************************************************/
void LineFrame::draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams)
{
    if ( !m_shaderProgram->bind() || !m_buffer.isCreated() ) {
        return;
    }

    m_buffer.bind();

    m_shaderProgram->setAttributeBuffer(m_attributeCoord2d, GL_FLOAT, 0, VERTEX_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeCoord2d);
    m_shaderProgram->setAttributeBuffer(m_attributeColors, GL_FLOAT, m_colorsOffset, COLOR_DIMENSIONS);
    m_shaderProgram->enableAttributeArray(m_attributeColors);

    m_buffer.release();

    m_shaderProgram->setUniformValue( m_uniformPvm, drawParams.projectionViewMatrix);

    for (int i = 0; i < LOOPS_COUNT; ++i) {
        int offset = i * RECT_VERTICES_COUNT;
        oglFunctions->glDrawArrays(GL_LINE_LOOP,offset,RECT_VERTICES_COUNT);
    }

    m_shaderProgram->disableAttributeArray(m_attributeColors);
    m_shaderProgram->disableAttributeArray(m_attributeCoord2d);

    m_shaderProgram->release();
}


/******************************************************************************
*   Замена шейдера
******************************************************************************/
void LineFrame::setShader(std::shared_ptr<QOpenGLShaderProgram> shader)
{
    m_shaderProgram = shader;

    bindShaderAttributes();
}


/******************************************************************************
*   Перезапись координат нижней правой точки рамки
******************************************************************************/
void LineFrame::expandFrame(QPointF position)
{
    m_buffer.bind();

    m_movablePoint[0] = position.y();
    m_movablePoint[1] = position.x();
    m_movablePoint[2] = position.y();
    m_movablePoint[3] = position.x();
    m_buffer.write(MOVABLE_DATA_OFFSET * sizeof(GLfloat), m_movablePoint.data(),sizeof(GLfloat) * m_movablePoint.size());

    for (int i = 1; i < LOOPS_COUNT; ++i) {
        int offset = (MOVABLE_DATA_OFFSET + i * RECT_VERTICES_COUNT * VERTEX_DIMENSIONS) * sizeof(GLfloat);
        m_movablePoint[0] -= LOOP_POSITION_DELTA;
        m_movablePoint[1] -= LOOP_POSITION_DELTA;
        m_movablePoint[2] -= LOOP_POSITION_DELTA;
        m_movablePoint[3] -= LOOP_POSITION_DELTA;
        m_buffer.write(offset, m_movablePoint.data(),sizeof(GLfloat) * m_movablePoint.size());
    }

    m_buffer.release();
}


/******************************************************************************
*   Создание буфера для меша
******************************************************************************/
void LineFrame::createBuffer()
{
    m_buffer.create();
    m_buffer.bind();
    m_buffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    int verticesPartSize = m_vertices.size() * sizeof(GLfloat);
    int colorsPartSize = m_colors.size() * sizeof(GLfloat);
    m_buffer.allocate(verticesPartSize + colorsPartSize);

    int offset = 0;
    m_buffer.write(offset, m_vertices.data(),verticesPartSize);
    offset += verticesPartSize;
    m_colorsOffset = offset;
    m_buffer.write(offset, m_colors.data(),colorsPartSize);

    m_buffer.release();
}


/******************************************************************************
*   Вычисление координат внутренних прямоугольников рамки
******************************************************************************/
void LineFrame::calcInnerLoops()
{
    int startIndex = RECT_VERTICES_COUNT * VERTEX_DIMENSIONS;
    int fininshIndex = VERTICES_COUNT * VERTEX_DIMENSIONS;
    int stepIndex = RECT_VERTICES_COUNT * VERTEX_DIMENSIONS;

    for (int i = startIndex, loop =1 ; i < fininshIndex; i += stepIndex, ++loop) {
        m_vertices[i]   = m_vertices[0] + LOOP_POSITION_DELTA * loop; // x top left
        m_vertices[i+1] = m_vertices[1] + LOOP_POSITION_DELTA * loop; // y top left
        m_vertices[i+2] = m_vertices[2] + LOOP_POSITION_DELTA * loop; // x top right
        m_vertices[i+3] = m_vertices[3] - LOOP_POSITION_DELTA * loop; // y top right
        m_vertices[i+4] = m_vertices[4] - LOOP_POSITION_DELTA * loop; // x bottom right
        m_vertices[i+5] = m_vertices[5] - LOOP_POSITION_DELTA * loop; // y bottom right
        m_vertices[i+6] = m_vertices[6] - LOOP_POSITION_DELTA * loop; // x bottom left
        m_vertices[i+7] = m_vertices[7] + LOOP_POSITION_DELTA * loop; // y bottom left
    }
}


/******************************************************************************
*   Привязка атрибутов шейдера
******************************************************************************/
void LineFrame::bindShaderAttributes()
{
    m_uniformPvm = m_shaderProgram->uniformLocation( SHADER_VARIABLES::UF_PVM_MATRIX );

    m_attributeCoord2d = m_shaderProgram->attributeLocation(SHADER_VARIABLES::ATR_COORD_2D);
    m_attributeColors = m_shaderProgram->attributeLocation(SHADER_VARIABLES::ATR_COLOR);
}

