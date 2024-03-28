#include "model.h"

Model::Model(QObject *parent)
    : QObject(parent)
    , sprite(defaultSpriteSize, backgroundColor)
    , currentFrame(sprite.addFrame())
    , currentTool(Tool::brush)
    , currentColor()
{
}

QImage *Model::newSprite(int size)
{
    sprite = Sprite(size, backgroundColor);
    currentFrame = sprite.addFrame();
    emit currentFrameChanged(currentFrame);
    return currentFrame;
}

QImage *Model::newFrame()
{
    currentFrame = sprite.addFrame();
    emit currentFrameChanged(currentFrame);
    return currentFrame;
}

void Model::setTool(Tool tool)
{
    currentTool = tool;
}

void Model::setColor(QColor color)
{
    currentColor = color;
}

void Model::actionOnPixel(int x, int y)
{
    switch (currentTool) {
    case Tool::brush:
        currentFrame->setPixelColor(x, y, currentColor);
        emit currentFrameChanged(currentFrame);
        break;
    case Tool::eraser:
        currentFrame->setPixelColor(x, y, backgroundColor);
        emit currentFrameChanged(currentFrame);
        break;
    }
}

