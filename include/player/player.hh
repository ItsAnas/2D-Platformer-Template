// typedef struct Player
// {
//     Vector2 position;
//     float speed;
//     bool canJump;
// } Player;
#pragma once

#include "raylib.h"

class Player
{
public:
    Player(Vector2 initialPosition)
        : position(initialPosition), speed(0), canJump(true){};

    Vector2 position;
    float speed;
    bool canJump;
};