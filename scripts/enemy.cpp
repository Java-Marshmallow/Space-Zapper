#include "../headers/enemy.h"

// Constructor sets up the enemies' texture, hitboxes and initial origin/target
Enemy::Enemy(Texture2D texture, Player player)
{
    // Stores enemy texture
    enemyTexture = texture;
    // Set up hitbox
    enemyRect.width = enemyTexture.width*scale;
    enemyRect.height = enemyTexture.height*scale;
    // Max x the enemies can reach
    randMaxX = GetScreenWidth() - enemyRect.width * 2;
    randMaxY = GetScreenHeight() - enemyRect.height * 2;
    // Set a random origin and target the player
    SetStartPos(player);
    SetTarget(player);
}

// Updates the enemies' positions and moves them
void Enemy::Move(Player player, float speed)
{
    // If the enemy goes off screen, reset its targetting so it moves back to the player which is always on screen
    if(enemyRect.x > randMaxX || enemyRect.x < 0 || enemyRect.y > randMaxY || enemyRect.y < 0) SetTarget(player);
    // If the enemy reaches its target
    if(distanceTravelled >= delta)
    {
        // Then it should retarget the player. It's a simple movement AI but I think it's fun
        distanceTravelled = 0;
        SetTarget(player);
    } else {
        // Same movement code as the bullet
        enemyRect.x += deltaX/delta * speed * GetFrameTime();
        enemyRect.y += deltaY/delta * speed * GetFrameTime();
        distanceTravelled += sqrt(pow(deltaX/delta * speed * GetFrameTime(), 2) + pow(deltaY/delta * 2 * GetFrameTime(), 2));
        Draw();
    }
}

void Enemy::Draw()
{
    // Draw enemies to the screen
    DrawTextureEx(enemyTexture, (Vector2){enemyRect.x, enemyRect.y}, 0, 2, WHITE);
}

// Sets the enemy to target the player
void Enemy::SetTarget(Player player)
{
    // Set the target to player
    target.x = player.GetRect().x;
    target.y = player.GetRect().y;
    // Calculate new distances
    deltaX = target.x - enemyRect.x;
    deltaY = target.y - enemyRect.y;
    delta = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

// At the start of a level, go to a random position
void Enemy::SetStartPos(Player player)
{
    // Pick a random new X and Y pos
    enemyRect.x = GetRandomValue(0, randMaxX);
    enemyRect.y = GetRandomValue(0, randMaxY);
    // If that new position is too close to the player then it should try again
    if(CheckCollisionRecs(enemyRect, player.GetSpawnRect())) SetStartPos(player);
}

// Return the rectangle for collisions
Rectangle Enemy::GetRect()
{
    return enemyRect;
}

// Iterates through every bullet to see if the enemy has collided with any of them, and return whether that's the case
bool Enemy::CheckBulletCollision(std::vector<Bullet> bulletList)
{
    for(int i = 0; i < bulletList.size(); i++) if(CheckCollisionRecs(enemyRect, bulletList.at(i).GetRect())) return true;
    return false;
}

