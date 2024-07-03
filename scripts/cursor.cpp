#include "../headers/cursor.h"

// Constructor sets the texture
Cursor::Cursor(Texture2D texture) 
{
    cursorTexture = texture;
}

// Draws the cursor at the mouse position
void Cursor::FindMouse()
{
    DrawTextureEx(cursorTexture, (Vector2){(float)GetMouseX() - cursorTexture.width, (float)GetMouseY() - cursorTexture.height}, 0, 2, WHITE);
}