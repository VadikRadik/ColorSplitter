#ifndef MESH_H
#define MESH_H

#include "OpenGLWidget/idrawable.h"

#include <QOpenGLBuffer>

#include <memory>


/******************************************************************************
*
*   A mesh with normals
*
******************************************************************************/
class Mesh : public IDrawable
{
public:
    Mesh(std::shared_ptr<QOpenGLShaderProgram> shader, GLenum drawMode);
    ~Mesh();

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override;

    void setVertices(std::vector<GLfloat> & vertices);
    void setNormals(std::vector<GLfloat> & normals);
    void setColors(std::vector<GLfloat> & colors);

    void createBuffer();

private:
    void bindShaderAttributes();

protected:
    std::shared_ptr<QOpenGLShaderProgram> m_shaderProgram;
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_normals;
    std::vector<GLfloat> m_colors;

    GLint m_attributeCoord3d;
    GLint m_attributeNormals;
    GLint m_attributeColors;

    GLint m_uniformLightDir;
    GLint m_uniformPvm;
    GLenum m_drawMode;

    QOpenGLBuffer m_buffer;
    QMatrix4x4 m_modelMatrix;

    int m_bufferSize;
    int m_colorsOffset;
    int m_normalsOffset;

    static const int VERTEX_DIMENSIONS = 3;
    static const int COLOR_DIMENSIONS = 3;
};

#endif // MESH_H
