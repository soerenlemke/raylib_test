//
// Created by soeren on 02.11.25.
//

#include "Block.h"

Block::Block(Vector2 pos, int w, int h) {
    this->position = pos;
    this->width = w;
    this->height = h;
}

void Block::Draw(Color color) const {
}

void Block::Destroy() {
}
