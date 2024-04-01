// Style Review completed by: Manya Nair
#ifndef PREVIEWANIMATION_H
#define PREVIEWANIMATION_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
    class previewAnimation;
}

// Sets up a class that will allow for the viewing of your different sprites in different frames per second.
class previewAnimation : public QMainWindow
{
    Q_OBJECT

public:
    explicit previewAnimation(Model *model,QWidget *parent = nullptr);
    ~previewAnimation();

private:
    Ui::previewAnimation *ui;
    Model *model;
};

#endif // PREVIEWANIMATION_H
