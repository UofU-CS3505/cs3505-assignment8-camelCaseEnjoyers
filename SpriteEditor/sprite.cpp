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
    if(getAmountOfFrames() > 1){
        frames.erase(frames.begin() + index - 1);
        if(index != 1){
            return &frames[index - 2];
        }
    }
    else{
        frames.first().fill(background);
    }
    return &frames.first();
}
int Sprite::getAmountOfFrames(){
    return frames.size();
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
