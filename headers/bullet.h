#include "raylib.h"
#include <cmath>

// The bullet class is a container for the bullets that are shot out to kill the aliens
class Bullet
{
    private:

    // Where the bullet will be sent to and where it starts
    Vector2 target, origin;
    // Bullet texture
    Texture2D bulletTexture;
    // Respectively: distance between target & origin on x/y axes, and total distance, and the current amount travelled
    float deltaX, deltaY, delta, distanceTravelled;
    // Bullet's collision rectangle
    float speedScale;

    public:

    // Whether or not the bullet has gone out of use
    bool isDeleted;

    // Methods
    Bullet(Vector2, Vector2, float, Texture2D);

    void ShootTick();

    Rectangle GetRect();
};
