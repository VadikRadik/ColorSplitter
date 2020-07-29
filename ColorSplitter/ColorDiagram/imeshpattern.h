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

protected:
    IMeshPattern() = default;

protected:
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_normals;
};

class ScalePartPattern : public IMeshPattern
{
public:
    ScalePartPattern();
private:
    const int VERTICES_COUNT = 48;
    const float INNER_R = 1.0f;
    const float OUTER_R = 1.1f;
    const float SEMIHEIGHT = 0.025f;
    const QVector3D UP = QVector3D(0.0f,1.0f,0.0);
};

#endif // IMESHPATTERN_H
