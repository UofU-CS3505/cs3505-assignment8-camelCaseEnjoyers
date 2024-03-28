#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model *model, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void userSelectedColor(QColor color);
public slots:
    void updateHistoryPallette(QColor colors[]);

private slots:
    void on_colorPickBtn_clicked();

private:
    Ui::MainWindow *ui;
    Model *model;
};
#endif // MAINWINDOW_H
