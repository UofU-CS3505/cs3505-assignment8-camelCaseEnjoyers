// Style Review completed by: Name Here
#include "model.h"
#include <iostream>
#include <QTimer>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
    transparent = QColor(QColorConstants::White);
    transparent.setAlpha(0);
    eraserState = false;
}

QImage *Model::newSprite(int size)
{
    sprite = Sprite(size, backgroundColor);
    currentFrame = sprite.addFrame();
    emit currentFrameChanged(currentFrame);
    emit changeFrameNum(1);
    emit frameMax(sprite.getAmountOfFrames());
    return currentFrame;
}

QImage *Model::newFrame()
{
    currentFrame = sprite.addFrame();
    frameNum += 1;
    emit frameMax(sprite.getAmountOfFrames());
    emit changeFrameNum(frameNum);
    emit currentFrameChanged(currentFrame);
    return currentFrame;
}

QImage *Model::deleteFrame(){
    currentFrame = sprite.deleteFrame(frameNum); //sets current frame as the frame before
    if(frameNum != 1)
        frameNum -= 1;
    emit changeFrameNum(frameNum);
    emit currentFrameChanged(currentFrame);
    emit frameMax(sprite.getAmountOfFrames()); //lowers max amount of frames
    return currentFrame;
}

void Model::setTool(Tool tool)
{
    currentTool = tool;
}

void Model::eraserSelected()
{
    eraserState = true;
    setColor(transparent);
}
void Model::penSelected()
{
    eraserState = false;
    setColor(recentColors[0]);
}

void Model::setColor(QColor color)
{
    if(color == transparent)
    {
        currentColor = transparent;
        return;
    }
    if(eraserState == true)
        return;
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
    //Do not update the view if we are changing to the eraser
    if(color == transparent)
        return;
    //Notify the view
    emit updateColorPallette(recentColors);

}

void Model::palletteColorSelected(int index)
{
    setColor(recentColors[index]);
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
void Model::changeFrameRate(int frame){
    frameRate = frame;
}

void Model::previewAnimation(){
    emit previewPressed(false); //disables preview button
    int waitTime;
    for(int i = 0; i < sprite.getAmountOfFrames(); i++){
        waitTime = i * (1000/frameRate); // queues each image to appear at a set frame rate
        QTimer::singleShot(waitTime, this, [=]{emit currentFrameChangedAnimation(sprite.getFrame(i)); return sprite.getFrame(i);});
    }
    waitTime = sprite.getAmountOfFrames() * 1000/frameRate;
    QTimer::singleShot(waitTime, this, [=]{emit previewPressed(true);}); //once animation is finishes re-enables button
}

void Model::selectFrame(int frame){
    currentFrame = sprite.getFrame(frame - 1);
    frameNum = frame;
    emit currentFrameChanged(currentFrame);
}

void Model::saveSprite(QString filename){
    //create file associated with directory from the view
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    //holds all Sprite data
    QJsonObject jsonSprite;
    //holds each frame of the sprite
    QJsonArray frames;
    int r;
    int g;
    int b;
    int a;

    for(QImage frame: sprite.frames){

        QJsonArray pixels;

        //iterate through each pixel of the current frame
        for(int i = 0; i < sprite.size; i++){
            for(int j = 0; j < sprite.size; j++){
                //extract colors from the pixel
                QColor color = frame.pixelColor(j,i);
                r = color.red();
                g = color.green();
                b = color.blue();
                a = color.alpha();
                //create pixel Json object to store color data
                QJsonObject pixel;

                pixel.insert("red", r);
                pixel.insert("green", g);
                pixel.insert("blue", b);
                pixel.insert("alpha", a);
                //add pixel to the frame
                pixels.append(pixel);
            }
        }
        //add the frame to the list of frames
        frames.append(pixels);
    }

    //store background color
    r = sprite.background.red();
    g = sprite.background.green();
    b = sprite.background.blue();
    a = sprite.background.alpha();
    QJsonObject background;
    background.insert("red", r);
    background.insert("green", g);
    background.insert("blue", b);
    background.insert("alpha", a);

    jsonSprite.insert("background", background);
    jsonSprite.insert("frames", frames);
    jsonSprite.insert("size", sprite.size);

    //turn Json object to Json and write it to the file
    QJsonDocument document;
    document.setObject(jsonSprite);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QTextStream iStream( &file );
    iStream << bytes;
    file.close();
}

void Model::loadSprite(QString filename){
    //load filename recived from the view
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    //read all data in the file
    QByteArray bytes = file.readAll();
    file.close();

    //check for an error in the Json
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
    if( jsonError.error != QJsonParseError::NoError )
    {
        std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
        return ;
    }
    if(document.isObject()){
        //turn text into Json object
        QJsonObject jsonSprite = document.object();

        //extract background and size information from Json object
        int size = jsonSprite.take("size").toInt();
        QJsonObject background = jsonSprite.take("background").toObject();
        QColor back;
        back.setRed(background.take("red").toInt());
        back.setGreen(background.take("green").toInt());
        back.setBlue(background.take("blue").toInt());
        back.setAlpha(background.take("alpha").toInt());

        //create new sprite with the saved background color and size
        sprite = Sprite(size, back);

        QJsonArray frames = jsonSprite.take("frames").toArray();
        QVector<QImage> images;

        //iterate through The Json array
        for(QJsonValue pixels: frames){
            QImage curFrame(size, size, QImage::Format_ARGB32);
            QJsonArray pixelAr = pixels.toArray();

            int xCord = 0;
            int yCord = 0;
            //for each pixel in the current frame
            for(QJsonValue color: pixelAr){

                //extract the pixel color
                QJsonObject curCol = color.toObject();
                int r = curCol.take("red").toInt();
                int g = curCol.take("green").toInt();
                int b = curCol.take("blue").toInt();
                int a = curCol.take("alpha").toInt();
                QColor pixelColor;
                pixelColor.setRed(r);
                pixelColor.setGreen(g);
                pixelColor.setBlue(b);
                pixelColor.setAlpha(a);

                //set current pixel at current postion to the correct color
                curFrame.setPixelColor(xCord, yCord, pixelColor);

                //incriment coordinate position values
                xCord++;
                if(xCord == size){
                    xCord = 0;
                    yCord++;
                    continue;
                }
            }
            images.append(curFrame);
        }

        //set sprite frames array to new decoded array
        sprite.frames = images;
        emit frameMax(sprite.getAmountOfFrames());
        currentFrame = &sprite.frames.first();
        //tell the canvas the frame has changed to update front end
        emit currentFrameChanged(&sprite.frames.first());
    }
}

