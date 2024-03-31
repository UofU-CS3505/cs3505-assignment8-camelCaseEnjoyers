#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QImage>
#include <QVector>

///
/// \brief The Sprite class contains all the data necessary to represent a sprite that can be edited and displayed
/// with the program. It contains all visual data on the sprite, how many frames it has, and its actual size.
///
class Sprite
{
public:
    Sprite(int size, const QColor &background);
    QImage *addFrame();
    QImage *deleteFrame(int);
    QImage *getFrame(int index = 0);
    int getAmountOfFrames();
    int size;
    QColor background;
    QVector<QImage> frames;
};

#endif // SPRITE_H
