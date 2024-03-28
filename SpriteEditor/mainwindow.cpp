#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Model *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(model)
{
    ui->setupUi(this);

    model->setColor(QColor(Qt::black));

    ui->canvas->setImage(model->getCurrentFrame());
    connect(ui->canvas,
            &Canvas::mouseOnPixel,
            model,
            &Model::actionOnPixel);
    connect(model,
            &Model::currentFrameChanged,
            ui->canvas,
            &Canvas::setImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
