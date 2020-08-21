#include "background.h"

Background::Background(const QColor &color)
    : m_color(color)
{

}


/******************************************************************************
*   Draws background
******************************************************************************/
void Background::draw(QOpenGLFunctions *oglFunctions, const DrawParameters &drawParams)
{
    oglFunctions->glClearColor(m_color.redF(), m_color.greenF(), m_color.blueF(), 1.0f);
}
