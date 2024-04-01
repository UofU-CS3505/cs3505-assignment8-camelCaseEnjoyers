// Style Review completed by: Name Here
#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QImage>

///
/// \brief The Canvas class records mouse data from the user that is utilized to draw pixels on the canvas.
///
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
    ///signals model to save the current sprite at the specified filename
    void saveSpriteName(QString filename);
    ///signals model to load a sprite from the specified filename
    void loadSpriteName(QString filename);


public slots:
    ///sets the current image the canvas is displaying
    void setImage(QImage* image);
    ///opens a save file dialog when a signal is sent from the export As button being pressed
    void savePNG();
    ///opens a save file dialog when a signal is sent from the save button being pressed
    void save();
    ///opens a load file dialog when a signal is sent from the load button being pressed
    void load();

private:
    ///a pointer to the current image being displayed by the canvas
    QImage *image;
};

#endif // CANVAS_H
