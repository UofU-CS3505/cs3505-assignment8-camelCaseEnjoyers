#include "model.h"
#include <iostream>

Model::Model(QObject *parent)
    : QObject(parent)
    , sprite(defaultSpriteSize, backgroundColor)
    , currentFrame(sprite.addFrame())
    , currentTool(Tool::brush)
    , currentColor()
{
    //Initialize currentColor to a default black
    currentColor = QColor(QColorConstants::Black);
    recentColors[0] = QColor(QColorConstants::Black);
    //Initialize color array to usable white instances
    for(int i = 1; i<5;i++)
        recentColors[i] = QColor(QColorConstants::White);

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
    //Check to see if the color the user chose is one they recently used
    if(!checkHistory(color))//This method
    {
        //If the color is not repeated, then update the display with the new color in the history pallette
        for(int i=4; i>0;i--)
        {
            recentColors[i] = recentColors[i-1];
        }
        recentColors[0] = color;
    }

    //And set the color to the newly selected color
    currentColor = color;
    //Notify the view

    emit updateColorPallette(recentColors);

}

bool Model::checkHistory(QColor newColor)
{
    //Check to see if the color is in the recent pallette
    for(int i = 0; i<5;i++)
        if(recentColors[i] == newColor)//if it is in the color pallette
        {
            //Move the color up to the front of the array, but keep the ordering of the other elements
            for(int index=i; index>0;index--)
            {
                recentColors[index] = recentColors[index-1];
            }
            recentColors[0] = newColor;
            return true;
        }
    //The array is always length 5 so if we made if here we are home free
    return false;
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

