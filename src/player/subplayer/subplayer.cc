#include <iostream>

#include "player/subplayer/subplayer.hh"

void Subplayer::print_random_shit()
{
    std::cout << "Saluuuuuuuuuuuuuuuuuuuuuuuuuut\n";
    std::cout << this->position.x << ':' << this->position.y << '\n';
}