#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(Model *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(model)
    , Animation(model)
{
    ui->setupUi(this);
    ui->canvas->setImage(model->getCurrentFrame());
    ui->chooseFrame->setMinimum(1);
    ui->chooseFrame->setMaximum(1);
    connect(ui->canvas,
            &Canvas::mouseOnPixel,
            model,
            &Model::actionOnPixel);
    connect(model,
            &Model::currentFrameChanged,
            ui->canvas,
            &Canvas::setImage);
    connect(ui ->addFrame,
            &QPushButton::clicked,
            model,
            &Model::newFrame);
    connect(model,
            &Model::frameMax,
            ui->chooseFrame,
            &QSpinBox::setMaximum);
    connect(ui ->deleteFramebtn,
            &QPushButton::clicked,
            model,
            &Model::deleteFrame);
    connect(ui -> chooseFrame,
            &QSpinBox::valueChanged,
            model,
            &Model::selectFrame);
    connect(ui -> exportBtn,
            &QPushButton::clicked,
            ui -> canvas,
            &Canvas::savePNG);
    connect(model,
            &Model::updateColorPallette,
            this,
            &MainWindow::updateHistoryPallette);
    connect(this,
            &MainWindow::userSelectedColor,
            model,
            &Model::setColor);
    connect(this,
            &MainWindow::userPalletteSelect,
            model,
            &Model::palletteColorSelected);
    connect(model,
            &Model::changeFrameNum,
             ui->chooseFrame,
            &QSpinBox::setValue);

    connect(ui -> saveBtn,
            &QPushButton::clicked,
            ui -> canvas,
            &Canvas::save);
    connect(ui -> canvas,
            &Canvas::saveSpriteName,
            model,
            &Model::saveSprite);
    connect(ui -> loadBtn,
            &QPushButton::clicked,
            ui -> canvas,
            &Canvas::load);
    connect(ui -> canvas,
            &Canvas::loadSpriteName,
            model,
            &Model::loadSprite);
    connect(this,
            &MainWindow::eraserSelected,
            model,
            &Model::eraserSelected);
    connect(this,
            &MainWindow::penSelected,
            model,
            &Model::penSelected);
    transparent = QColor(QColorConstants::White);
    transparent.setAlpha(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playAnimation_clicked(){
    Animation.show();
}

void MainWindow::updateHistoryPallette(QColor colors[])
{
    //Set button color 0
    std::string rgbCode = "rgb("+std::to_string((colors[0]).red())+", "+std::to_string((colors[0]).green())+", "+std::to_string((colors[0]).blue())+")";
    QString styleSheet = QString::fromStdString("QPushButton{border:none;background-color:"+rgbCode+";}");
    ui->colorhistorybtn0->setStyleSheet(styleSheet);

    //Set button color 1
    rgbCode = "rgb("+std::to_string((colors[1]).red())+", "+std::to_string((colors[1]).green())+", "+std::to_string((colors[1]).blue())+")";
    styleSheet = QString::fromStdString("QPushButton{border:none;background-color:"+rgbCode+";}");
    ui->colorhistorybtn1->setStyleSheet(styleSheet);

    //Set button color 2
    rgbCode = "rgb("+std::to_string((colors[2]).red())+", "+std::to_string((colors[2]).green())+", "+std::to_string((colors[2]).blue())+")";
    styleSheet = QString::fromStdString("QPushButton{border:none;background-color:"+rgbCode+";}");
    ui->colorhistorybtn2->setStyleSheet(styleSheet);

    //Set button color 3
    rgbCode = "rgb("+std::to_string((colors[3]).red())+", "+std::to_string((colors[3]).green())+", "+std::to_string((colors[3]).blue())+")";
    styleSheet = QString::fromStdString("QPushButton{border:none;background-color:"+rgbCode+";}");
    ui->colorhistorybtn3->setStyleSheet(styleSheet);

    //Set button color 4
    rgbCode = "rgb("+std::to_string((colors[4]).red())+", "+std::to_string((colors[4]).green())+", "+std::to_string((colors[4]).blue())+")";
    styleSheet = QString::fromStdString("QPushButton{border:none;background-color:"+rgbCode+";}");
    ui->colorhistorybtn4->setStyleSheet(styleSheet);
}

void MainWindow::on_colorPickBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        // Send the selected color to the model
        emit userSelectedColor(color);
    }
}

void MainWindow::on_colorhistorybtn1_clicked()
{
    emit userPalletteSelect(1);
}
void MainWindow::on_colorhistorybtn2_clicked()
{
    emit userPalletteSelect(2);
}
void MainWindow::on_colorhistorybtn3_clicked()
{
    emit userPalletteSelect(3);
}
void MainWindow::on_colorhistorybtn4_clicked()
{
    emit userPalletteSelect(4);
}




void MainWindow::on_penToggle_clicked()
{
    ui->penToggle->setChecked(true);
    ui->eraseToggle->setChecked(false);
    emit penSelected();
}


void MainWindow::on_eraseToggle_clicked()
{
    ui->penToggle->setChecked(false);
    ui->eraseToggle->setChecked(true);
    emit eraserSelected();
}

