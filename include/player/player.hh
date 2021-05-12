#pragma once

#include "raylib.h"

class Player
{
public:
    Player(Vector2 initialPosition)
        : position(initialPosition), speed(0), canJump(true){};

    virtual void print_random_shit();

    Vector2 position;
    float speed;
    bool canJump;
};
