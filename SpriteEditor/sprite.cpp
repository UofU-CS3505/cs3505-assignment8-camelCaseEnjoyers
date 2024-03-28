#include "sprite.h"

#include <QColor>

Sprite::Sprite(int size, const QColor &background)
    : size(size)
    , background(background)
    , frames()
{

}

QImage *Sprite::addFrame()
{
    frames.append(QImage(size, size, QImage::Format_ARGB32));
    frames.last().fill(background);
    return &frames.last();
}

QImage *Sprite::getFrame(int index)
{
    if (index < 0)
    {
        return &frames.first();
    }
    if (index >= frames.size())
    {
        return &frames.last();
    }
    return &frames[index];
}
