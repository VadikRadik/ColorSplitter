#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include "OpenGLWidget/abstractscene.h"

class ImageScene : public AbstractScene
{
public:
    ImageScene(ICamera *camera);

    virtual void initialize() override;

    void setImage(const QImage & image);

private:
    std::shared_ptr<QOpenGLShaderProgram> m_rasterImageShader;
};

#endif // IMAGESCENE_H
