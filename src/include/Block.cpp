//
// Created by soeren on 02.11.25.
//

#include "Block.h"

Block::Block(Vector2 pos, int w, int h) : position(pos), width(w), height(h) {}

void Block::Draw(const Color color) const {
    DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
}

void Block::Destroy() {
    if (!alive) return;
    if (onDestroyed) onDestroyed();

    alive = false;
}

Rectangle Block::GetRect() const {
    return Rectangle(position.x, position.y, static_cast<float>(width), static_cast<float>(height));
}
