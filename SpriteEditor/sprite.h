#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QImage>
#include <QVector>

class Sprite
{
public:
    Sprite(int size, const QColor &background);
    QImage *addFrame();
    QImage *deleteFrame(int);
    QImage *getFrame(int index = 0);
    int amtOfFrames;
    int size;
    QColor background;
    QVector<QImage> frames;

private:
};

#endif // SPRITE_H
