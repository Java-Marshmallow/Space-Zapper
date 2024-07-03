#include "raylib.h"

// All this does is replace the default cursor with a texture
class Cursor
{
    private:

    // Stores the cursor's texture
    Texture2D cursorTexture;

    public:

    // Methods
    Cursor(Texture2D);

    void FindMouse();

};