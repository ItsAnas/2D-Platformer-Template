#include "player.hh"

#include <iostream>

Player::Player(Vector2 initialPosition)
    : position(initialPosition)
    , speed(0)
    , canJump(true)
{}