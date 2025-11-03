//
// Created by soeren on 02.11.25.
//

#include "../include/Paddle.h"

Paddle::Paddle(const Vector2 pos, const int w, const int h, const float speed) : position(pos), width(w), height(h), speed(speed) {}

void Paddle::Update(const float dt, const int screenWidth) {
    if (IsKeyDown(KEY_D))
        position.x += speed * dt;
    if (IsKeyDown(KEY_A))
        position.x -= speed * dt;
    // Keep paddle within screen bounds
    if (position.x < 0)
        position.x = 0;
    if (position.x > static_cast<float>(screenWidth - width))
        position.x = static_cast<float>(screenWidth - width);
}

void Paddle::Draw(const Color color) const {
    DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
}

Rectangle Paddle::GetRect() const {
    return {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}
