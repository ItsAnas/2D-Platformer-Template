#pragma once

#include <utility>
#include <vector>

#include "player.hh"
#include "world_bloc.hh"

class World
{
public:
    World(std::vector<WorldBlock> worldblocks);
    ~World();

    void Draw() const;
    int CountBlocks() const;
    bool CheckCollision(Player &p, float delta) const;

private:
    std::vector<WorldBlock> &_blocks;
};

World::World(std::vector<WorldBlock> worldblocks)
    : _blocks(worldblocks)
{}

World::~World()
{}

void World::Draw() const
{
    for (unsigned i = 0; i < _blocks.size(); i++)
    {
        DrawRectangleRec(_blocks[i]._rect, _blocks[i]._color);
    }
}

int World::CountBlocks() const
{
    return _blocks.size();
}

bool World::CheckCollision(Player &p, float delta) const
{
    bool hitObstacle = false;
    for (unsigned i = 0; i < _blocks.size(); i++)
    {
        WorldBlock &block = _blocks[i];
        if (block._blocking && block._rect.x <= p.position.x
            && block._rect.x + block._rect.width >= p.position.x
            && block._rect.y >= p.position.y
            && block._rect.y < p.position.y + p.speed * delta)
        {
            hitObstacle = true;
            p.speed = 0.0f;
            p.position.y = block._rect.y;
        }
    }

    return hitObstacle;
}