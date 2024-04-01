// Style Review completed by: Name Here
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"
#include "previewanimation.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

///
/// \brief The MainWindow class connects the view to the model. It contains an instance of the model and the Ui, and
/// it connects all signals to slots, allowing the front and backend to communicate appropriately.
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model *model, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    /// @brief tells the model which color the user selected
    /// @param the color chosen by the user in the color pick menu
    void userSelectedColor(QColor color);
    /// @brief tells the model that the user selected acolor from the color pallette.
    /// @param number corresponding to the button selected 0-4
    void userPalletteSelect(int btnNum);
    /// @brief signals eraser select to the model
    void eraserSelected();
    /// @brief signals pen select to model
    void penSelected();
public slots:
    /// @brief changes the appearance of the view's color pallette to match the 5 most recent colors used by the user
    /// @param colors the array of colors to be represented
    void updateHistoryPallette(QColor colors[]);

private slots:
    /// @brief sends a signal to the model containing the color the user wants to swap to
    void on_colorPickBtn_clicked();

    /// @brief sends a signal that the color in box #2 has been selected to the model
    void on_colorhistorybtn1_clicked();
    /// @brief sends a signal that the color in box #3 has been selected to the model
    void on_colorhistorybtn2_clicked();
    /// @brief sends a signal that the color in box #4 has been selected to the model
    void on_colorhistorybtn3_clicked();
    /// @brief sends a signal that the color in box #5 has been selected to the model
    void on_colorhistorybtn4_clicked();

    void on_playAnimation_clicked();

    /// @brief notifies the model to update the tool to the pen
    void on_penToggle_clicked();

    /// @brief notifies the model to update the tool to eraser
    void on_eraseToggle_clicked();

    void on_newSpriteBtn_clicked();

private:
    Ui::MainWindow *ui;
    Model *model;
    previewAnimation Animation;
    /// A color that designates the eraser
    QColor transparent;
};
#endif // MAINWINDOW_H
