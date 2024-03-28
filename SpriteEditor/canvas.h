#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QImage>

class Canvas : public QLabel
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);

protected:
    inline virtual void mouseMoveEvent(QMouseEvent *ev) override { processMouseEvent(ev); }
    inline virtual void mousePressEvent(QMouseEvent *ev) override { processMouseEvent(ev); }
    inline virtual void mouseReleaseEvent(QMouseEvent *ev) override { processMouseEvent(ev); }

private:
    inline int imageX(int canvasX) const { return image->width() * canvasX / width(); }
    inline int imageY(int canvasY) const { return image->height() * canvasY / height(); }
    void processMouseEvent(QMouseEvent *ev);

signals:
    void mouseOnPixel(int x, int y);

public slots:
    void setImage(QImage* image);
    void savePNG();

private:
    QImage *image;
};

#endif // CANVAS_H
