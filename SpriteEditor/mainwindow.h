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
    void userSelectedColor(QColor color);
    void userPalletteSelect(int btnNum);
public slots:
    void updateHistoryPallette(QColor colors[]);

private slots:
    void on_colorPickBtn_clicked();

    void on_colorhistorybtn1_clicked();

    void on_colorhistorybtn2_clicked();

    void on_colorhistorybtn3_clicked();

    void on_colorhistorybtn4_clicked();

    void on_playAnimation_clicked();

private:
    Ui::MainWindow *ui;
    Model *model;
    previewAnimation Animation;
};
#endif // MAINWINDOW_H
