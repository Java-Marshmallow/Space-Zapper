#include "../headers/player.h"

// Constructor, sets up player texture, hitbox and spawn range
Player::Player(Texture2D texture, Texture2D death, float scale)
{
    // Set up player texture and scale
    playerTexture = texture;
    textureScale = scale;
    // Move player to center
    Reset();
    // Set up hitbox
    playerRect.width = texture.width * scale - offset*2;
    playerRect.height = texture.height * scale - offset*2;
    // Set up the enemy spawn exclusion area based on the distance specified
    enemySpawnRect.width = playerRect.width + enemySpawnDist * 2;
    enemySpawnRect.height = playerRect.height + enemySpawnDist * 2;
    enemySpawnRect.x = playerRect.x - enemySpawnDist;
    enemySpawnRect.y = playerRect.y - enemySpawnDist;
    // Set up death texture
    deathImage = death;
}

// Draw player texture
void Player::Draw() 
{
    // If you lose, draw the death texture, otherwise draw the normal one
    if(lose) DrawTextureEx(deathImage, (Vector2){playerRect.x - offset, playerRect.y - offset}, 0, textureScale, WHITE);
    else DrawTextureEx(playerTexture, (Vector2){playerRect.x - offset, playerRect.y - offset}, 0, textureScale, WHITE); 
}

// Check collision with other rectangle (read: enemy) and set lose bool
void Player::CheckCollisionEnemy(Rectangle otherRect)
{
    if(CheckCollisionRecs(playerRect, otherRect)) lose = true;
}

// Calculate player velocity and move
void Player::Move() 
{
    // Move based on calculated velocities
    playerRect.x += xVel;
    playerRect.y += yVel;

    // If player goes too far right, move them back in and reset their velocity
    if(playerRect.x + playerRect.width + offset > GetScreenWidth()) 
    {
        playerRect.x = GetScreenWidth() - playerRect.width - offset; 
        xVel = 0;
    } 
    // If player goes too far left, move them back in
    else if(playerRect.x - offset < 0) 
    {
        playerRect.x = offset; 
        xVel = 0;
    }

    // Same as X check but for y
    if(playerRect.y + playerRect.height + offset > GetScreenHeight()) 
    {
        playerRect.y = GetScreenHeight() - playerRect.height - offset; 
        yVel = 0;
    } 
    else if(playerRect.y - offset < 0) 
    {
        playerRect.y = offset; 
        yVel = 0;
    }

    // If arrow key or correspondinf WASD key is pressed and the velocity limjt hasn't yet been reached, increase the velocity.
    // This makes for smooth movements.
    if(IsKeyDown(KEY_A) && xVel >= -6) xVel -= accel; 
    else if (IsKeyDown(KEY_D) && xVel <= 6) xVel += accel;
    // If keys aren't pressed, decelerate
    else if (xVel < 0) xVel += accel; else if (xVel > 0) xVel -= accel;

    // Same as left and right movements but for y axis
    if(IsKeyDown(KEY_W) && yVel >= -6) yVel -= accel; 
    else if (IsKeyDown(KEY_S) && yVel <= 6) yVel += accel;
    else if (yVel < 0) yVel += accel; else if (yVel > 0) yVel -= accel;
}

// Get the center of the player, used to set the bullet position
Vector2 Player::GetCenterPos()
{
    return (Vector2){playerRect.x + playerRect.width/2, playerRect.y + playerRect.height/2};
}

// Get the status of the lose variable to see if the player HasLost()
bool Player::HasLost()
{
    return lose;
}

// Put the player in the middle and set lose to false, also reset velocities
void Player::Reset()
{
    playerRect.x = GetScreenWidth()/2 - playerTexture.width + offset;
    playerRect.y = GetScreenHeight()/2 - playerTexture.height + offset;
    lose = false;
    xVel = 0;
    yVel = 0;
}

// Returns hitbox/spawn exclusion area
Rectangle Player::GetRect()
{
    return playerRect;
}

Rectangle Player::GetSpawnRect()
{
    return enemySpawnRect;
}