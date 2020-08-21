#include "meshpack.h"


MeshPack::MeshPack()
{

}


/******************************************************************************
*   Adds a mesh to the pack
******************************************************************************/
void MeshPack::addMesh(std::shared_ptr<IDrawable> mesh)
{
    m_meshes.push_back(mesh);
}


/******************************************************************************
*   Draws all pack's meshes
******************************************************************************/
void MeshPack::draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams)
{
    for (auto & mesh : m_meshes)
        mesh->draw(oglFunctions,drawParams);
}


/******************************************************************************
*   Changes the shader
******************************************************************************/
void MeshPack::setShader(std::shared_ptr<QOpenGLShaderProgram> shader)
{
    for (auto & mesh : m_meshes)
        mesh->setShader(shader);
}
