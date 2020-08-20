#include "colordiagramview.h"
#include "OpenGLWidget/centred3deulercamera.h"
#include "DrawableObjects/mesh.h"
#include "uistrings.h"

#include <QGroupBox>

/******************************************************************************
*   Constructor
******************************************************************************/
ColorDiagramView::ColorDiagramView(std::shared_ptr<ColorDiagramController> controller)
    : m_diagramWidget(nullptr)
    , m_lightSwitch(new QCheckBox(UI_STRINGS::LIGHT_SWITCH))
    , m_tetrahedronShape(new QRadioButton(UI_STRINGS::TETRAHEDRON_SHAPE))
    , m_cubeShape(new QRadioButton(UI_STRINGS::CUBE_SHAPE))
    , m_octahedronShape(new QRadioButton(UI_STRINGS::OCTAHEDRON_SHAPE))
    , m_icosahedronShape(new QRadioButton(UI_STRINGS::ICOSAHEDRON_SHAPE))
    , m_controller(controller)
{
    m_cubeShape->setChecked(true);
    m_lightSwitch->setChecked(true);
    std::shared_ptr<ColorDiagramScene> scene = std::make_shared<ColorDiagramScene>(new Centred3DEulerCamera());

    m_diagramWidget = new OpenGLWidget(scene);
    m_controller->bindScene(scene);
    m_scene = scene;
}


/******************************************************************************
*   Creates user's input handlers
******************************************************************************/
void ColorDiagramView::createLogic(QWidget* widget) const
{
    widget->connect(m_lightSwitch,&QCheckBox::toggled,[=](bool checked) {
        m_controller->switchLight(checked);
        m_diagramWidget->update();
    });

    widget->connect(m_tetrahedronShape,&QRadioButton::pressed,[=](){
        m_controller->setShape(EDiagramDotShape::TETRAHEDRON);
        m_diagramWidget->update();
    });
    widget->connect(m_cubeShape,&QRadioButton::pressed,[=](){
        m_controller->setShape(EDiagramDotShape::CUBE);
        m_diagramWidget->update();
    });
    widget->connect(m_octahedronShape,&QRadioButton::pressed,[=](){
        m_controller->setShape(EDiagramDotShape::OCTAHEDRON);
        m_diagramWidget->update();
    });
    widget->connect(m_icosahedronShape,&QRadioButton::pressed,[=](){
        m_controller->setShape(EDiagramDotShape::ICOSAHEDRON);
        m_diagramWidget->update();
    });
}


/******************************************************************************
*   Returns the view widget
******************************************************************************/
QWidget *ColorDiagramView::createWidget() const
{
    QWidget * widget = new QWidget();

    QHBoxLayout * mainLayout = new QHBoxLayout();

    mainLayout->addLayout(createControls(),1);
    mainLayout->addWidget(m_diagramWidget,15);

    widget->setLayout(mainLayout);

    createLogic(widget);

    return widget;
}


/******************************************************************************
*   Updates the view by changing of a model state
******************************************************************************/
void ColorDiagramView::update(const ColorSplitterModel *model, EModelUpdates stateChange)
{
    switch (stateChange) {
    case EModelUpdates::IMAGE_DECOMPOSED:
        m_controller->fillDiagram();
        m_diagramWidget->update();
        break;
    default:
        break;
    }
}


/******************************************************************************
*   Creates controls
******************************************************************************/
QVBoxLayout *ColorDiagramView::createControls() const
{
    QVBoxLayout * viewControlsLayout = new QVBoxLayout();

    QGroupBox * shapeWaysWaysBox = new QGroupBox(UI_STRINGS::DIAGRAM_POINTS_SHAPE);
    QVBoxLayout * shapeWaysLayout = new QVBoxLayout();

    shapeWaysLayout->addWidget(m_tetrahedronShape);
    shapeWaysLayout->addWidget(m_cubeShape);
    shapeWaysLayout->addWidget(m_octahedronShape);
    shapeWaysLayout->addWidget(m_icosahedronShape);
    shapeWaysWaysBox->setLayout(shapeWaysLayout);

    viewControlsLayout->addWidget(m_lightSwitch);
    viewControlsLayout->addWidget(shapeWaysWaysBox);
    viewControlsLayout->addStretch();

    return viewControlsLayout;
}
