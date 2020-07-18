#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <QString>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

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
};

/******************************************************************************
*
*   Интерфейс отрисовываемого объекта
*
******************************************************************************/
class IDrawable
{
public:
    virtual ~IDrawable() {}

    virtual void draw(QOpenGLFunctions * oglFunctions, const DrawParameters & drawParams) = 0;
    virtual void initialize() = 0;
};

#endif // IDRAWABLE_H
