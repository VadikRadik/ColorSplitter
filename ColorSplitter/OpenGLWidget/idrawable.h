#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <QString>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <memory>

namespace SHADER_VARIABLES {
    const QString ATR_COORD_2D          = "pos2d";
    const QString ATR_COORD_3D          = "pos3d";
    const QString ATR_COLOR             = "color";
    const QString ATR_NORMAL            = "normal";
    const QString ATR_TEXTURE_COORDS    = "textureCoords";

    const QString UF_PVM_MATRIX         = "pvm";
    const QString UF_LIGHT_DIRECTION    = "lightDir";
    const QString UF_TEXTURE            = "sampler";
    const QString UF_COLOR              = "uniformColor";
}

struct DrawParameters
{
    QMatrix4x4 pvm;
    QMatrix4x4 projectionViewMatrix;
    QVector3D lightDirection;
};

/******************************************************************************
*
*   An interface of drawable objects
*
******************************************************************************/
class IDrawable
{
public:
    virtual ~IDrawable() {}

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) = 0;
    virtual void setShader(std::shared_ptr<QOpenGLShaderProgram> shader) = 0;
};

#endif // IDRAWABLE_H
