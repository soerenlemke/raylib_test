//
// Created by soeren on 02.11.25.
//

#include "Block.h"

Block::Block(Vector2 pos, int w, int h) : position(pos), width(w), height(h) {}

void Block::Draw(Color color) const {
    if (!alive)
        return;
    DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
}

void Block::Destroy() { alive = false; }
