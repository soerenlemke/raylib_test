//
// Created by soeren on 02.11.25.
//

#include "Ball.h"

Ball::Ball(float radius, Vector2 pos, Vector2 vel)
    : position(pos), velocity(vel), radius(radius) {
}

void Ball::Update(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Ball::Draw(Color color) const {
    DrawCircleV(position, radius, color);
}

void Ball::Reset(Vector2 pos, Vector2 vel) {
    position = pos;
    velocity = vel;
}
