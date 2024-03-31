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

///
/// \brief The Model class is the backend for the sprite editor software, as specified by the MVC architecture.
/// The model takes in information from the view, and perfroms any necessary logic, manipulates the current sprite's data,
/// and lets the canvas know when it needs to update.
///
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    inline QImage* getCurrentFrame() const { return currentFrame; }

signals:
    void currentFrameChanged(QImage *frame);
    void currentFrameChangedAnimation(QImage *frame);
    void updateColorPallette(QColor colors[]);
    void previewPressed(bool);
    void changeFrameNum(int);

public slots:
    QImage *newSprite(int size);
    QImage *newFrame();
    QImage *deleteFrame();
    void setTool(Tool tool);
    void setColor(QColor color);
    void palletteColorSelected(int index);
    void actionOnPixel(int x, int y);
    void previewAnimation();
    void selectFrame(int);
    void changeFrameRate(int);

    /// \brief slot that responds to the saveSpriteName signal in the canvas. Recives the filename the user specified
    /// from the front end, creates a file with that name, and converts all sprite related data into Json and writes it
    /// to the file.
    /// \param filename
    void saveSprite(QString filename);
    /// \brief slot that responds to the loadSpriteName signal in the canvas. Recives teh filename the user specified
    /// from the front end, opens the specified file (it must be .ssp), converts Json data into a sprite object, and
    /// sets that to the model's sprite field.
    /// \param filename
    void loadSprite(QString filename);

private:
    ///sprite holds the sprite's size, and all its pixel information
    Sprite sprite;
    ///a pointer to the frame currently being displayed by the canvas
    QImage *currentFrame;
    ///enum representing which drawing tool is currently selected by the user
    Tool currentTool;
    ///the current color of the brush
    QColor currentColor;
    ///array that is used to store the last 5 colors the user drew with
    QColor recentColors[5];
    bool checkHistory(QColor newColor);
    ///represents how quickly frames are cycled through when viewing the animation preview
    int frameRate = 1;
    ///represents which frame the model is currently displaying
    int frameNum = 1;

public:
    ///size the sprite will be if not otherwise specifed by the user
    static constexpr int defaultSpriteSize = 32;
    ///color that the background of the canvas will be filled with by default
    static inline const QColor backgroundColor = QColor(Qt::white);
};

#endif // MODEL_H
