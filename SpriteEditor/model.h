#ifndef MODEL_H
#define MODEL_H

#include "sprite.h"

#include <QObject>
#include <QColor>
#include <QImage>

enum class Tool
{
    brush,
    eraser,
};

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    inline QImage* getCurrentFrame() const { return currentFrame; }

signals:
    void currentFrameChanged(QImage *frame);
    void updateColorPallette(QColor colors[]);

public slots:
    QImage *newSprite(int size);
    QImage *newFrame();
    void setTool(Tool tool);
    void setColor(QColor color);
    void palletteColorSelected(int index);
    void actionOnPixel(int x, int y);

private:
    Sprite sprite;
    QImage *currentFrame;
    Tool currentTool;
    QColor currentColor;
    QColor recentColors[5];
    bool checkHistory(QColor newColor);

public:
    static constexpr int defaultSpriteSize = 32;
    static inline const QColor backgroundColor = QColor(Qt::white);
};

#endif // MODEL_H
