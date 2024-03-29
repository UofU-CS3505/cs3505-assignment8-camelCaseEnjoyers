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

QImage *Sprite::deleteFrame(int index)
{
    frames.erase(frames.begin() + index - 1);
    return &frames[index - 1];
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
    amtOfFrames = frames.size();
    return &frames[index];
}
