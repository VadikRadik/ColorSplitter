#ifndef MESHPACK_H
#define MESHPACK_H

#include "OpenGLWidget/idrawable.h"

/******************************************************************************
*
*   Обёртка для коллекции мешей
*
******************************************************************************/
class MeshPack : public IDrawable
{
public:
    MeshPack();

    void addMesh(std::shared_ptr<IDrawable> mesh);
    virtual void draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams) override;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) override;

private:
    std::list<std::shared_ptr<IDrawable>> m_meshes;
};

#endif // MESHPACK_H
