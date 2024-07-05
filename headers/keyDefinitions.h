#include "raylib.h"

// Makes it easy to quickly change what keys do what in the game. As few keys as possible are used to emulate the behavior of the platform that inspired the game, the NES
enum PreDefinedKey
{
    LEFT = KEY_A,
    RIGHT = KEY_D,
    UP = KEY_W,
    DOWN = KEY_S,
    SHOOT = KEY_SPACE,
    SWITCH_MODE = KEY_Q,
    PAUSE = KEY_ENTER
};