#include "meshpack.h"

MeshPack::MeshPack()
{

}

void MeshPack::addMesh(std::shared_ptr<IDrawable> mesh)
{
    m_meshes.push_back(mesh);
}

void MeshPack::draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams)
{
    for (auto & mesh : m_meshes)
        mesh->draw(oglFunctions,drawParams);
}
