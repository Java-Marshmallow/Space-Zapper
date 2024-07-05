#include "../headers/cursor.h"

// Constructor sets the texture
Cursor::Cursor(Texture2D texture, float scale) 
{
    cursorTexture = texture;
    cursorRect.width = cursorTexture.width * scale;
    cursorRect.height = cursorTexture.height * scale;
}

// Calculate velocity and move, similar to player
void Cursor::Move(float speed) 
{
    // If arrow keys are pressed, change the cursor's x
    if(IsKeyDown(KEY_LEFT)) cursorRect.x -= speed; 
    else if (IsKeyDown(KEY_RIGHT)) cursorRect.x += speed;

    // Same as left and right movements but for y axis
    if(IsKeyDown(KEY_UP)) cursorRect.y -= speed; 
    else if (IsKeyDown(KEY_DOWN)) cursorRect.y += speed;

    // Correct the x and y coordinates if the cursor leaves the screen
    if(cursorRect.x + cursorRect.width > GetScreenWidth()) 
    {
        cursorRect.x = GetScreenWidth() - cursorRect.width; 
    } 
    else if(cursorRect.x < 0) 
    {
        cursorRect.x = 0; 
    }

    // Same as X check but for Y
    if(cursorRect.y + cursorRect.height > GetScreenHeight()) 
    {
        cursorRect.y = GetScreenHeight() - cursorRect.height; 
    } 
    else if(cursorRect.y < 0) 
    {
        cursorRect.y = 0; 
    }
}

void Cursor::Draw()
{
    DrawTextureEx(cursorTexture, (Vector2){cursorRect.x, cursorRect.y}, 0, 2, WHITE);
}

Vector2 Cursor::GetCursorCenter()
{
    return (Vector2){cursorRect.x + cursorRect.width/2, cursorRect.y + cursorRect.height/2};
}