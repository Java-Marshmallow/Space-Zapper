#include "raylib.h"

// Container for the player, including all their positional data, movements, etc.
class Player 
{
    private:

    // How much the texture should be scaled up
    float textureScale;
    // Player's default/death textures
    Texture2D playerTexture, deathImage;
    // Player hitbox, and the range in which enemies can spawn
    Rectangle playerRect, enemySpawnRect;
    // X & Y velocity & how much the player should speed up
    float yVel = 0;
    float xVel = 0;
    float accel = 1;
    // Whether you've lost, false by default
    bool lose = false;
    // How much the hitbox is offset from the texture
    const float offset = 3;
    // How far away enemies can spawn from the player
    float enemySpawnDist = 30;

    public:

    Player(Texture2D, Texture2D, float);

    void Draw();

    void Move();

    Vector2 GetCenterPos();

    bool HasLost();

    void Reset();

    Rectangle GetRect();

    void CheckCollisionEnemy(Rectangle);

    Rectangle GetSpawnRect();
};