#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>

class Canvas : public QLabel
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);

private:
    QImage *image;
};

#endif // CANVAS_H
