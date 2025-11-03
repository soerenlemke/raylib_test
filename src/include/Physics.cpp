//
// Created by soeren on 03.11.25.
//

#include "Physics.h"

#include <raylib.h>

#include "Ball.h"
#include "Paddle.h"

void Physics::Update(Ball &ball, const Paddle &paddle, std::vector<Block> &blocks, const int screenWidth,
                     const int screenHeight) {
    CheckBallCollisionsWithWalls(ball, screenWidth);
    CheckBallCollisionsWithPaddle(ball, paddle);
    CheckBallCollisionsWithBlocks(ball, blocks);
    CheckBallOffscreen(ball, screenWidth, screenHeight);
}

void Physics::CheckBallCollisionsWithWalls(Ball &ball, const int screenWidth) {
    if (ball.GetPosition().x - ball.GetRadius() <= 0) {
        Vector2 p = ball.GetPosition();
        p.x = ball.GetRadius();
        ball.Reset(p, Vector2{-ball.GetVelocity().x, ball.GetVelocity().y});
    } else if (ball.GetPosition().x + ball.GetRadius() >= static_cast<float>(screenWidth)) {
        Vector2 p = ball.GetPosition();
        p.x = static_cast<float>(screenWidth) - ball.GetRadius();
        ball.Reset(p, Vector2{-ball.GetVelocity().x, ball.GetVelocity().y});
    }
    if (ball.GetPosition().y - ball.GetRadius() <= 0) {
        Vector2 p = ball.GetPosition();
        p.y = ball.GetRadius();
        ball.Reset(p, Vector2{ball.GetVelocity().x, -ball.GetVelocity().y});
    }
}

void Physics::CheckBallCollisionsWithPaddle(Ball &ball, const Paddle &paddle) {
    Rectangle pad = paddle.GetRect();
    if (CheckCollisionCircleRec(ball.GetPosition(), ball.GetRadius(), pad) && ball.GetVelocity().y > 0) {
        Vector2 p = ball.GetPosition();
        p.y = pad.y - ball.GetRadius();
        Vector2 v = ball.GetVelocity();
        v.y *= -1;

        const float hitNorm = ((p.x - (pad.x + pad.width * 0.5f)) / (pad.width * 0.5f));
        v.x += hitNorm * 200.0f; // increase lateral velocity based on hit position

        ball.Reset(p, v);
    }
}

void Physics::CheckBallCollisionsWithBlocks(Ball &ball, std::vector<Block> &blocks) {
    // TODO: implement
}

void Physics::CheckBallOffscreen(Ball &ball, const int screenWidth, const int screenHeight) {
    if (ball.GetPosition().y - ball.GetRadius() > static_cast<float>(screenHeight)) {
        ball.Reset(Vector2{static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f},
                   Vector2{200.0f, 200.0f});
    }
}
