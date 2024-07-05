#include "raylib.h"
#include <string>
#include <vector>
#include "../headers/textBox.h"
#include "../headers/cursor.h"
#include "../headers/enemy.h"
#include "../headers/keyDefinitions.h"

/**********************************************************
*                                                         *
*   To-do list:                                           *
*                                                         *      
*   Add controller support                                *
*                                                         *      
************************************************************/

using namespace std;

enum MoveMode
{
    PLAYER,
    CURSOR
};

int main()
{
    // Initialize the window & audio, set FPS and hide the cursor
    InitWindow(256, 240, "Space Zapper");
    InitAudioDevice();
    SetTargetFPS(60);
    HideCursor();

    // Initialize variables that'll be used in-game
    int score = 0;
    int hiScore = 0;
    int resetTick = 0;
    int enemyCount = 2;
    float enemySpeed = 0.5;
    bool paused = false;
    MoveMode currentMode = PLAYER;

    // Load textures
    Texture2D pTex = LoadTexture("../assets/images/ufo.png");
    Texture2D eTex = LoadTexture("../assets/images/enemy.png");
    Texture2D bTex = LoadTexture("../assets/images/bullet.png");

    // Load sounds
    Sound death = LoadSound("../assets/sounds/explosion.wav");
    Sound shoot = LoadSound("../assets/sounds/laserShoot.wav");

    // Load game font
    Font gameFont = LoadFont("../assets/fonts/sprint-2.ttf");

    // Create the player object
    Player player(pTex, LoadTexture("../assets/images/explosion.png"), 2);

    // Create a cursor instance
    Cursor cursor(LoadTexture("../assets/images/cursor.png"), 2);

    // Create the text boxes
    TextBox scoreBox(gameFont, ("score " + to_string(score)), 12, 0, 0, 5);
    TextBox hiScoreBox(gameFont, ("hiscore\n" + to_string(hiScore)), 12, 145.5, 0, 5);
    TextBox pauseBox(gameFont, "paused", 12, GetScreenWidth()/2 - 43, GetScreenHeight()/2 - 6, 5);
    // Center the pause text
    pauseBox.SetPosition((Vector2){GetScreenWidth()/2 - pauseBox.GetRect().width/2, GetScreenHeight()/2 - pauseBox.GetRect().height/2});

    // Create the vectors to store the bullets and enemies
    vector<Bullet> bulletList;
    vector<Enemy> enemyList(enemyCount, Enemy(eTex, player));
    
    // Main gameplay loop. Everything in here happens 60 times every second.
    while(!WindowShouldClose())
    {
        // Begin the drawing to the screen
        BeginDrawing();

        // resetTick pauses the game for 2 seconds (120 ticks) before resetting
        if(resetTick == 0)
        {
            // The game should pause like that if you lose or if you beat the level
            if(player.HasLost() || enemyList.size() == 0) resetTick = 1;
            if(!paused)
            {
                // Wipe the screen
                ClearBackground(BLACK);

                // Set move mode based on whether a key is pressed
                if(IsKeyDown(SWITCH_MODE)) 
                {
                    currentMode = CURSOR;
                    if(IsKeyPressed(SWITCH_MODE))cursor.Center(player.GetRect());
                } else currentMode = PLAYER;

                // For every enemy, the player checks if they've collided with it.
                for(int i = 0; i < enemyList.size(); i++) player.CheckCollisionEnemy(enemyList[i].GetRect());

                // Draw player
                player.Draw();

                // When the mouse is clicked, create a new bullet and add it to the bullet list.
                if(IsKeyPressed(SHOOT)) 
                {
                    // Set the bullet position to the player position and add the bullet to the beginning of the bullet list.
                    // This makes sense since the first bullet to be destroyed will be the last one added to the list.
                    Bullet bullet(cursor.GetCursorCenter(), player.GetCenterPos(), 5, bTex);
                    bulletList.insert(bulletList.begin(), bullet);
                    PlaySound(shoot);
                }

                // Update every bullet in the list and check if it needs to be deleted.
                for(int i = 0; i < bulletList.size(); i++) {
                    bulletList.at(i).ShootTick();
                    if(bulletList.at(i).isDeleted)
                    {
                        bulletList.pop_back();
                    }
                }

                // Update the enemies.
                for(int i = 0; i < enemyList.size(); i++) 
                {
                    // Draw the enemies, and reset them once they hit their target
                    enemyList[i].Draw(player, enemySpeed); 
                    
                    // If the enemy hits a bullet, remove the enemy from the list. This was difficult to implement
                    if(enemyList[i].CheckBulletCollision(bulletList)) 
                    {
                        enemyList.erase(enemyList.begin() + i);
                        score++;
                        if(score > hiScore) hiScore = score;
                    }
                }

                // Draw text boxes to the screen 
                scoreBox.DrawText(); 
                scoreBox.SetText("score\n" + std::to_string(score));

                hiScoreBox.DrawText(); 
                hiScoreBox.SetText("hiscore\n" + std::to_string(hiScore));

                // Change what moves based on current move mode
                if(currentMode == PLAYER) player.Move(); 
                else 
                {
                    cursor.Move(6);
                    // Draw the cursor
                    cursor.Draw();
                }

                if(player.HasLost()) PlaySound(death);
            }
            if(IsKeyPressed(PAUSE)) 
            {
                if(paused == false) paused = true;
                else paused = false;
            }

            // If the game is paused draw a textbos showing so
            if(paused) pauseBox.DrawText();
        }
        // Wait for 2 seconds to elapse
        else if(resetTick < 120) resetTick++;
        // Executed once 2 seconds have elapsed.
        else
        {
            // Reset resetTick so the gameplay loop goes again
            resetTick = 0;
            // There are 2 scenarios where resetTick is used, when you lose or when you increase your level. Only reset score if you've lost.
            if(player.HasLost()) 
            {
                score = 0;
                enemyCount = 2;
                enemySpeed = 0.5;
            }
            else 
            {
                enemyCount++;
                enemySpeed += 0.1;
            }
            // Put the player back at the center of the screen, and reset the enemies/bullets.
            player.Reset();
            enemyList.clear();
            bulletList.clear();
            enemyList.assign(enemyCount, Enemy(eTex, player));
            for(int i = 0; i < enemyList.size(); i++)
            {
                enemyList[i].SetTarget(player);
                enemyList[i].SetStartPos(player);
            }
        }

        EndDrawing();
    }
    
    // Once the game loop has been given a signal to stop, the window closes and the game is done
    bulletList.clear();
    enemyList.clear();
    UnloadFont(gameFont);
    UnloadTexture(pTex);
    UnloadTexture(eTex);
    UnloadTexture(bTex);
    UnloadSound(death);
    UnloadSound(shoot);
    
    CloseWindow();
    return 0;
}