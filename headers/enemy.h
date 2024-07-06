#include "raylib.h"
#include "./player.h"
#include "./bullet.h"
#include <vector>
#include <time.h>
#include <cstdlib>
#include <cmath>

// Container for enemies and their movements.
class Enemy
{
    private:

    // Stores the enemies' texture and collision rectangles
    Texture2D enemyTexture;
    Rectangle enemyRect;
    // Stores the enemies' target (the player)
    Vector2 target;
    // Movement is taken from bullet code
    float delta, deltaX, deltaY, distanceTravelled;
    // Maximum values where the enemies can travel. 
    // Apparently this isn't completely foolproof(?) so there's more code to keep them in the screen
    int randMaxX;
    int randMaxY;
    // How big the enemies are
    float scale = 2;

    public:

    // Whether enemy is alive
    bool isAlive = true;

    // Methods
    Enemy(Texture2D, Player);

    void Move(Player, float);

    void Draw();

    void SetTarget(Player);

    void SetStartPos(Player);

    Rectangle GetRect();

    bool CheckBulletCollision(std::vector<Bullet>);
};