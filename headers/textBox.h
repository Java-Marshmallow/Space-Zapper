#include "raylib.h"
#include <string>

// Container for any text
class TextBox
{
    private:

    // Font to be used
    Font textBoxFont;
    // What to show
    std::string textBoxText;
    // Font size
    int textBoxFontSize;
    // Rectangle containing the text
    Rectangle textBoxRect;
    // Text box size
    Vector2 textBoxSize;
    // How much the text should be offset from its rectangle
    float textBoxMargin;

    public:

    // Methods
    TextBox(Font, std::string, int, float, float, float);

    void DrawText();

    void SetText(std::string);

    bool CheckCollision();

    Rectangle GetRect();

    void SetPosition(Vector2);
};