// Style Review completed by: Name Here
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
    /// \brief signals the view to update the colors displayed on the history pallette
    void updateColorPallette(QColor colors[]);
    ///
    /// \brief disables preview button when the animation is playing
    ///
    void previewPressed(bool);
    ///
    /// \brief sets the value of the current QImage frame to whatever is in the spinBox
    ///
    void changeFrameNum(int);
    ///
    /// \brief sets a max frame number so that the user cannot go to a frame that does not exist
    ///
    void frameMax(int);

public slots:
    QImage *newSprite(int size);
    QImage *newFrame();
    QImage *deleteFrame();
    void setTool(Tool tool);

    /// @brief changes the user's pen color in the model
    /// @param color the color that the user selected(sent by the view)
    void setColor(QColor color);
    /// @brief changes the user's pen color to one of their 5 most recently used colors
    /// @param index an int that represents the index of the color in the recent colors array. corresponds to button number in the view
    void palletteColorSelected(int index);
    /// @brief triggered when the eraser is selected. changes the pen color to clear and locks the ability to change colors.
    void eraserSelected();
    /// @brief triggered when the pen is selected. changes the pen color to the users most recent color and reenables the ability to change colors
    void penSelected();

    void actionOnPixel(int x, int y);

    ///
    /// \brief displays the animation sequence at the desired framerate
    ///
    void previewAnimation();
    ///
    /// \brief when the value of the spinbox chooseFrame is altered, is selects the
    ///  frame that matches the number in spinbox
    ///
    void selectFrame(int);
    ///
    /// \brief alters the framerate for the animation sequence based off of the
    /// slider and the spinbox
    ///
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
    /// @brief Checks to see if the color selected is one used in the past 5 color swaps. Changes the recentColors array to reflect this change if the color is in the last 5
    /// @param newColor the color provided to this method by the setColor method
    /// @return true if the color was recently selected, false if not
    bool checkHistory(QColor newColor);
    ///represents how quickly frames are cycled through when viewing the animation preview
    int frameRate = 1;
    ///represents which frame the model is currently displaying
    int frameNum = 1;
    ///A custom color the represents the eraser. Used to prevent the color pallette from updating abnormally when selecting the eraser
    QColor transparent;
    ///A bool representing the eraser state. false if the eraser is not in use and true otherwise
    bool eraserState;

public:
    ///size the sprite will be if not otherwise specifed by the user
    static constexpr int defaultSpriteSize = 32;
    ///color that the background of the canvas will be filled with by default
    static inline const QColor backgroundColor = QColor(0, 0, 0, 1);
};

#endif // MODEL_H
