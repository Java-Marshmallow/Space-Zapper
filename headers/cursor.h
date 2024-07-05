#include "raylib.h"

// All this does is replace the default cursor with a texture
class Cursor
{
    private:

    // Cursor's rectangle
    Rectangle cursorRect;

    // Stores the cursor's texture
    Texture2D cursorTexture;

    public:

    // Methods
    Cursor(Texture2D, float);

    void Move(float);

    void Draw();

    Vector2 GetCursorCenter();

    void Center(Rectangle);
};