//
// Created by soeren on 03.11.25.
//

#include "Physics.h"

#include <algorithm>
#include <cmath>
#include <raylib.h>

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"

void Physics::Update(Ball &ball, const Paddle &paddle, std::vector<Block> &blocks, const int screenWidth,
                     const int screenHeight) {
    CheckBallCollisionsWithWalls(ball, screenWidth);
    CheckBallCollisionsWithPaddle(ball, paddle);
    CheckBallCollisionsWithBlocks(ball, blocks);
    CheckBallOffscreen(ball, screenWidth, screenHeight);
    ClearDeadBlocks(blocks);
}

void Physics::CheckBallCollisionsWithWalls(Ball &ball, const int screenWidth) {
    if (ball.GetPosition().x - ball.GetRadius() <= 0) {
        Vector2 p = ball.GetPosition();
        p.x = ball.GetRadius();
        ball.SetPosition(p);
        ball.SetVelocity(Vector2{-ball.GetVelocity().x, ball.GetVelocity().y});
    } else if (ball.GetPosition().x + ball.GetRadius() >= static_cast<float>(screenWidth)) {
        Vector2 p = ball.GetPosition();
        p.x = static_cast<float>(screenWidth) - ball.GetRadius();
        ball.SetPosition(p);
        ball.SetVelocity(Vector2{-ball.GetVelocity().x, ball.GetVelocity().y});
    }
    if (ball.GetPosition().y - ball.GetRadius() <= 0) {
        Vector2 p = ball.GetPosition();
        p.y = ball.GetRadius();
        ball.SetPosition(p);
        ball.SetVelocity(Vector2{ball.GetVelocity().x, -ball.GetVelocity().y});
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

        ball.SetPosition(p);
        ball.SetVelocity(v);
    }
}

void Physics::CheckBallCollisionsWithBlocks(Ball &ball, std::vector<Block> &blocks) {
    for (auto &block : blocks) {
        Rectangle rect = block.GetRect();
        if (!CheckCollisionCircleRec(ball.GetPosition(), ball.GetRadius(), rect)) continue;

        Vector2 ballPosition = ball.GetPosition();

        const float closestX = std::clamp(ballPosition.x, rect.x, rect.x + rect.width);
        const float closestY = std::clamp(ballPosition.y, rect.y, rect.y + rect.height);
        const Vector2 closest{ closestX, closestY };

        Vector2 diff{ ballPosition.x - closest.x, ballPosition.y - closest.y };

        // If the circle center lies exactly inside the rectangle (edge case), determine direction to the nearest edge
        if (diff.x == 0.0f && diff.y == 0.0f) {
            float left = ballPosition.x - rect.x;
            float right = rect.x + rect.width - ballPosition.x;
            float top = ballPosition.y - rect.y;
            float bottom = rect.y + rect.height - ballPosition.y;
            float minDist = std::min(std::min(left, right), std::min(top, bottom));
            if (minDist == left) diff = { -1.0f, 0.0f };
            else if (minDist == right) diff = { 1.0f, 0.0f };
            else if (minDist == top) diff = { 0.0f, -1.0f };
            else diff = { 0.0f, 1.0f };
        }

        Vector2 v = ball.GetVelocity();

        // Decide whether collision is horizontal or vertical (smaller penetration -> choose axis)
        if (std::fabs(diff.x) > std::fabs(diff.y)) {
            // horizontal collision: invert X component and place ball outside the block
            v.x = -v.x;
            if (diff.x > 0) ballPosition.x = closest.x + ball.GetRadius();
            else ballPosition.x = closest.x - ball.GetRadius();
        } else {
            // vertical collision: invert Y component and place ball outside the block
            v.y = -v.y;
            if (diff.y > 0) ballPosition.y = closest.y + ball.GetRadius();
            else ballPosition.y = closest.y - ball.GetRadius();
        }

        ball.SetPosition(ballPosition);
        ball.SetVelocity(v);

        block.Destroy();
    }
}

void Physics::CheckBallOffscreen(Ball &ball, const int screenWidth, const int screenHeight) {
    if (ball.GetPosition().y - ball.GetRadius() > static_cast<float>(screenHeight)) {
        ball.Respawn(Vector2{static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f});
    }
}

void Physics::ClearDeadBlocks(std::vector<Block> &blocks) {
    std::erase_if(blocks, [](const Block &block) { return !block.IsAlive(); });
}
