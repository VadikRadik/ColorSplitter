#include "colordiagramview.h"
#include "OpenGLWidget/centred3deulercamera.h"
#include "DrawableObjects/mesh.h"
#include "uistrings.h"

#include <QGroupBox>

/******************************************************************************
*   Конструктор
******************************************************************************/
ColorDiagramView::ColorDiagramView()
    : m_diagramWidget(nullptr)
    , m_lightSwitch(new QCheckBox(UI_STRINGS::LIGHT_SWITCH))
    , m_cubeShape(new QRadioButton(UI_STRINGS::CUBE_SHAPE))
    , m_icosahedronShape(new QRadioButton(UI_STRINGS::ICOSAHEDRON_SHAPE))
{
    m_cubeShape->setChecked(true);
    m_lightSwitch->setChecked(true);
    std::shared_ptr<ColorDiagramScene> scene = std::make_shared<ColorDiagramScene>(new Centred3DEulerCamera());

    m_diagramWidget = new OpenGLWidget(scene);
    m_scene = scene;
}


/******************************************************************************
*   Создание и/или передача виджета представления
******************************************************************************/
QWidget *ColorDiagramView::createWidget() const
{
    QWidget * widget = new QWidget();

    QHBoxLayout * mainLayout = new QHBoxLayout();

    mainLayout->addLayout(createControls(),1);
    mainLayout->addWidget(m_diagramWidget,15);

    widget->setLayout(mainLayout);

    return widget;
}


/******************************************************************************
*   Обновление представления по событию изменения модели
******************************************************************************/
void ColorDiagramView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{

}


/******************************************************************************
*   Создание элементов управления виджета представления
******************************************************************************/
QVBoxLayout *ColorDiagramView::createControls() const
{
    QVBoxLayout * viewControlsLayout = new QVBoxLayout();

    QGroupBox * shapeWaysWaysBox = new QGroupBox(UI_STRINGS::DIAGRAM_POINTS_SHAPE);
    QVBoxLayout * shapeWaysLayout = new QVBoxLayout();

    shapeWaysLayout->addWidget(m_cubeShape);
    shapeWaysLayout->addWidget(m_icosahedronShape);
    shapeWaysWaysBox->setLayout(shapeWaysLayout);

    viewControlsLayout->addWidget(m_lightSwitch);
    viewControlsLayout->addWidget(shapeWaysWaysBox);
    viewControlsLayout->addStretch();

    return viewControlsLayout;
}
