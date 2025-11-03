//
// Created by soeren on 02.11.25.
//

#include "../include/Ball.h"

#include <cmath>

Ball::Ball(const Vector2 pos, const float radius, const Vector2 vel) : position(pos), velocity(vel), radius(radius) {
    Respawn(pos);
}

void Ball::Update(const float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Ball::Draw(const Color color) const { DrawCircleV(position, radius, color); }

// TODO: how to keep the speed consistent but randomize direction?
void Ball::Respawn(const Vector2 pos) {
    position = pos;

    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed < 1e-6f) speed = 200.0f;

    constexpr float angle = 45.0f * (M_PI / 180.0f);

    const float side = (static_cast<float>(GetRandomValue(0, 100)) / 100.0f) * 2.0f - 1.0f;

    velocity.x = static_cast<float>(side) * speed * std::cos(angle);
    velocity.y = speed * std::sin(angle);
}
