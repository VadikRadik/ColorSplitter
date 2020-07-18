#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "OpenGLWidget/scene.h"

class SceneBuilder
{
public:
    SceneBuilder();

    void setCamera(ICamera * camera);

    std::shared_ptr<Scene> build();

private:
    ICamera * m_camera;
};

#endif // SCENEBUILDER_H
