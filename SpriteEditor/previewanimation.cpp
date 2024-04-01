#include "previewanimation.h"
#include "ui_previewanimation.h"

previewAnimation::previewAnimation(Model *model,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::previewAnimation)
    , model(model)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(60);
    ui->horizontalSlider->setTickPosition(ui->horizontalSlider->TicksBelow);
    ui->horizontalSlider->setTickInterval(5);
    connect(model,
            &Model::currentFrameChangedAnimation,
            ui->canvasAnimation,
            &Canvas::setImage);
    // connection between the previewanimation button and the pop up screen for it 
    connect(ui->previewAnimation_2,
            &QPushButton::clicked,
            model,
            &Model::previewAnimation);
    // starts the preview of your animation
    connect(model,
            &Model::previewPressed,
            ui->previewAnimation_2,
            &QPushButton::setEnabled);
    // tracks what the fps is set to
    connect(ui->spinBox,
            &QSpinBox::valueChanged,
            model,
            &Model::changeFrameRate);
    // disallows repeated pressed of the preview till the end of the preview
    connect(model,
            &Model::previewPressed,
            ui-> spinBox,
            &QSpinBox::setEnabled);
}
previewAnimation::~previewAnimation()
{
    delete ui;
}
