#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include "OpenGLWidget/abstractscene.h"

class ImageScene : public AbstractScene
{
public:
    ImageScene(ICamera *camera);

    virtual void initialize() override;

    void changeImage(const QImage & image);

private:
    std::shared_ptr<QOpenGLShaderProgram> m_rasterImageShader;
    std::weak_ptr<IDrawable> m_image;
};

#endif // IMAGESCENE_H
