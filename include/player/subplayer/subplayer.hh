#pragma once

#include <raylib.h>
#include "player/player.hh"

class Subplayer : public Player
{
public:
    Subplayer(Vector2 initialPosition, int tqt)
        : Player(initialPosition), tqt(tqt){};

    void print_random_shit() override;

    int tqt;
};