#include "drawOnCanvas.h"
#include <QPainter>
#include <QMouseEvent> // Include this line

drawOnCanvas::drawOnCanvas(QWidget *parent) : QGraphicsView(parent)
{
    // Initialize any necessary variables here
    // For example, set a default color
    currentColor = Qt::black;
}

void drawOnCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        currentPath.moveTo(event->pos());
    }
}

void drawOnCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        currentPath.lineTo(event->pos());
        update(); // Redraw the canvas
    }
}

void drawOnCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Finalize the path or perform any necessary actions
    }
}

void drawOnCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    painter.setPen(QPen(currentColor, 5)); // Use the current color and a pen width of 5
    painter.drawPath(currentPath);
}

void drawOnCanvas::setCurrentColor(const QColor &color) {
    currentColor = color;
}
