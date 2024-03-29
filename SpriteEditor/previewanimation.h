#ifndef PREVIEWANIMATION_H
#define PREVIEWANIMATION_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
class previewAnimation;
}

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
