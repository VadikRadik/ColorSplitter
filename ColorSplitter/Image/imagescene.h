#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include "OpenGLWidget/abstractscene.h"
#include "DrawableObjects/lineframe.h"

class ImageScene : public AbstractScene
{
public:
    ImageScene(ICamera *camera);

    virtual void initialize() override;

    void changeImage(const QImage & image);
    void expandFrame(QPoint position);
    void createFrame(QPoint position);
    void removeFrame();

    QRect getFrameRect() const;

private:
    std::shared_ptr<QOpenGLShaderProgram> m_rasterImageShader;
    std::weak_ptr<IDrawable> m_image;
    std::shared_ptr<QOpenGLShaderProgram> m_lineFrameShader;
    std::weak_ptr<LineFrame> m_frame;

    QPoint m_topLeftFrame;
    QPoint m_bottomRightFrame;
};

#endif // IMAGESCENE_H
