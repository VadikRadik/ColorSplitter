#ifndef LINEFRAME_H
#define LINEFRAME_H

#include "OpenGLWidget/idrawable.h"

#include <QOpenGLBuffer>


/******************************************************************************
*
*   A rectangle frame
*
******************************************************************************/
class LineFrame : public IDrawable
{
public:
    LineFrame(std::shared_ptr<QOpenGLShaderProgram> shader, QPointF startPosition);

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override;

    void expandFrame(QPointF position);

private:
    void bindShaderAttributes();
    void createBuffer();
    void calcInnerLoops();

private:
    static constexpr int VERTEX_DIMENSIONS = 2;
    static constexpr int COLOR_DIMENSIONS = 3;
    static constexpr int LOOPS_COUNT = 3;
    static constexpr int RECT_VERTICES_COUNT = 4;
    static constexpr int VERTICES_COUNT = LOOPS_COUNT * RECT_VERTICES_COUNT;
    static constexpr int VERTICES_ARRAY_SIZE = VERTICES_COUNT * VERTEX_DIMENSIONS;
    static constexpr int COLORS_ARRAY_SIZE = VERTICES_COUNT * COLOR_DIMENSIONS;
    static constexpr int MOVABLE_DATA_OFFSET = 3;

    const GLfloat LOOP_POSITION_DELTA = 1.0f;

    std::shared_ptr<QOpenGLShaderProgram> m_shaderProgram;
    std::array<GLfloat,VERTICES_ARRAY_SIZE> m_vertices;
    std::array<GLfloat,COLORS_ARRAY_SIZE> m_colors;

    GLint m_attributeCoord2d;
    GLint m_attributeColors;
    GLint m_uniformPvm;

    QOpenGLBuffer m_buffer;

    int m_bufferSize;
    int m_colorsOffset;

    std::array<GLfloat,4> m_movablePoint;
};

#endif // LINEFRAME_H
