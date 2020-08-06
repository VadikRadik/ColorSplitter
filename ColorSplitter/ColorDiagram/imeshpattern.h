#ifndef IMESHPATTERN_H
#define IMESHPATTERN_H

#include <vector>
#include <QOpenGLFunctions>

#include <QVector3D>

class IMeshPattern
{
public:
    virtual ~IMeshPattern() {}

    virtual std::vector<GLfloat> vertices() const {return m_vertices;}
    virtual std::vector<GLfloat> normals() const {return m_normals;}
    virtual int patternDataSize() const {return m_vertices.size();}
    virtual GLenum drawMode() = 0;

protected:
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_normals;
};

class CubePattern : public IMeshPattern
{
public:
    CubePattern();

    virtual GLenum drawMode() override {return GL_QUADS; }

private:
    const int VERTICES_COORDINATES_COUNT = 72;
    const float HALF_RIB = 0.5f;
    const int VERTICES_PER_FACE = 4;
};

class TetrahedronPattern : public IMeshPattern
{
public:
    TetrahedronPattern();

    virtual GLenum drawMode() override {return GL_TRIANGLES; }

private:
    const int VERTICES_COORDINATES_COUNT = 36;
    const float SPHERE_R = 0.5f;
    const int VERTICES_PER_FACE = 3;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
};

class OctahedronPattern : public IMeshPattern
{
public:
    OctahedronPattern();

    virtual GLenum drawMode() override {return GL_TRIANGLES; }

private:
    const int VERTICES_COORDINATES_COUNT = 72;
    const float SPHERE_R = 0.5f;
    const int VERTICES_PER_FACE = 3;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
};

class Icosahedron : public IMeshPattern
{
public:
    Icosahedron();

    virtual GLenum drawMode() override {return GL_TRIANGLES; }

private:
    const int VERTICES_COORDINATES_COUNT = 180;
    const float HALF_RIB = 0.2f;
    const int VERTICES_PER_FACE = 3;
};

class ScalePartPattern : public IMeshPattern
{
public:
    ScalePartPattern();

    virtual GLenum drawMode() override {return GL_QUADS; }

private:
    const int VERTICES_COORDINATES_COUNT = 48;
    const float INNER_R = 1.1f;
    const float OUTER_R = 1.2f;
    const float SEMIHEIGHT = 0.025f;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
};

#endif // IMESHPATTERN_H
