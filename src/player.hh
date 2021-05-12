#pragma once

#include "raylib.h"

class Player
{
public:
    Player(Vector2 initialPosition);

    Vector2 position;
    float speed;
    bool canJump;
};
