#ifndef DRAWONCANVAS_H
#define DRAWONCANVAS_H

#include <QGraphicsView>
#include <QPainterPath>
#include <QColor>

class DrawOnCanvas : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DrawOnCanvas(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPainterPath currentPath;
    QColor currentColor;

public slots:
    void setCurrentColor(const QColor &color);
};

#endif // DRAWONCANVAS_H
