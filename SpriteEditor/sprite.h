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
    QImage *getFrame(int index = 0);

private:
    int size;
    QColor background;
    QVector<QImage> frames;
};

#endif // SPRITE_H
