#pragma once

#include "raylib.h"

class WorldBlock
{
public:
    WorldBlock(Rectangle rect, bool blocking, Color color);
    ~WorldBlock();

    Rectangle _rect;
    bool _blocking;
    Color _color;
};

WorldBlock::WorldBlock(Rectangle rect, bool blocking, Color color)
    : _rect(rect)
    , _blocking(blocking)
    , _color(color)
{}

WorldBlock::~WorldBlock()
{}
