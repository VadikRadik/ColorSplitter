#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include <vector>
#include <memory>

#include <QOpenGLFunctions>

#include "imeshpattern.h"

class MeshBuilder
{
public:
    MeshBuilder(std::shared_ptr<IMeshPattern> pattern, int builderSize);

    bool addMeshByPattern(const QMatrix4x4 & modelMatrix, const QColor & color);

    std::vector<GLfloat> & resultVertices();
    std::vector<GLfloat> & resultNormals();
    std::vector<GLfloat> & resultColors();

private:
    std::vector<GLfloat> m_patternVertices;
    std::vector<GLfloat> m_patternNormals;

    std::vector<GLfloat> m_resultVertices;
    std::vector<GLfloat> m_resultNormals;
    std::vector<GLfloat> m_resultColors;

    int m_batchFloatsSize;
    int m_patternFloatsCount;
};

#endif // MESHBUILDER_H
