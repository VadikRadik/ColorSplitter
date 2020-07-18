#include "scenebuilder.h"

SceneBuilder::SceneBuilder()
    : m_camera(nullptr)
{

}

void SceneBuilder::setCamera(ICamera *camera)
{
    m_camera = camera;
}

std::shared_ptr<Scene> SceneBuilder::build()
{
    std::shared_ptr<Scene> result = std::make_shared<Scene>();
    result->setCamera(std::move(m_camera));
    return result;
}
