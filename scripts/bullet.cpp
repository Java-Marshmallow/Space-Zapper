#include "../headers/bullet.h"

// Constructor creates a new bullet at the player position and sets up the target at where the mouse is
Bullet::Bullet(Vector2 newTarget, Vector2 newOrigin, float speed, Texture2D texture)
{
    // Set up bullet dimensions and origin
    bulletRect.height = bulletRect.width = 10;
    bulletRect.x = newOrigin.x - bulletRect.width/2;
    bulletRect.y = newOrigin.y - bulletRect.height/2;

    // Calculate the distance that needs to be travelled on the x and y axes as well as the total distance needed
    deltaX = newTarget.x - bulletRect.x;
    deltaY = newTarget.y - bulletRect.y;
    delta = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    // Obviously starting out it's not going to be deleted and will not have travelled at all
    isDeleted = false;
    distanceTravelled = 0;

    // Store texture and speed
    bulletTexture = texture;

    speedScale = speed;
}

// Moves the bullet every frame and determines when it should be destroyed
void Bullet::ShootTick() // This took way longer than I would care to admit
{
    // If the bullet has gone the total distance required, it deletes itself
    if(distanceTravelled >= delta)
    {
        isDeleted = true;
        distanceTravelled = 0;
    } else { 
        // I'm not sure how this math works but it does so I'm not touching it
        bulletRect.x += deltaX/delta * speedScale * GetFrameTime() * 70;
        bulletRect.y += deltaY/delta * speedScale * GetFrameTime() * 70;
        // Distance travelled is calculated using Pythagorean Theorem
        distanceTravelled += sqrt(pow(deltaX/delta * speedScale * GetFrameTime() * 70, 2) + pow(deltaY/delta * speedScale * GetFrameTime() * 70, 2));
        Draw();
    }
}

void Bullet::Draw()
{
    // Draw Bullet
    DrawTextureEx(bulletTexture, (Vector2){bulletRect.x, bulletRect.y}, 0, 2, WHITE);
}

// Return the rectangle of the bullet (for collisions and stuff)
Rectangle Bullet::GetRect()
{
    return bulletRect;
}