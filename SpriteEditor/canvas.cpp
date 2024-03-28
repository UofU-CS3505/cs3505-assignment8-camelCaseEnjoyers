#include "canvas.h"

#include <QColor>
#include <QMouseEvent>
#include <QPixmap>

Canvas::Canvas(QWidget* parent)
    : QLabel(parent)
    , image()
{
}

void Canvas::processMouseEvent(QMouseEvent *ev)
{
    int canvasX = ev->pos().x();
    int canvasY = ev->pos().y();
    if (canvasX < 0 || canvasX >= width() || canvasY < 0 || canvasY >= height())
    {
        return;
    }
    int x = imageX(canvasX);
    int y = imageY(canvasY);
    emit mouseOnPixel(x, y);
}

void Canvas::setImage(QImage *image)
{
    this->image = image;
    setPixmap(QPixmap::fromImage(image->scaled(width(), height())));
}
