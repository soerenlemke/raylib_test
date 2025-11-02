#include <cmath>
#include <iostream>
#include "raylib.h"

int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    constexpr int playerHeight = 30;
    constexpr int playerWidth = 100;
    constexpr float ballRadius = 10.0f;

    InitWindow(screenWidth, screenHeight, "raylib-test");

    // player
    Vector2 playerPosition = {
        static_cast<float>(screenWidth)/2-static_cast<float>(playerWidth)/2,
        static_cast<float>(screenHeight)-playerHeight
    };

    // ball
    Vector2 ballPosition = {
        static_cast<float>(screenWidth)/2,
        static_cast<float>(screenHeight)/2
    };
    Vector2 ballVelocity = { 200.0f, 200.0f };

    SetTargetFPS(120);

    // main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // player movement
        if (IsKeyDown(KEY_D)) playerPosition.x += 300.0f * dt;
        if (IsKeyDown(KEY_A)) playerPosition.x -= 300.0f * dt;

        // limit player to screen bounds
        if (playerPosition.x < 0) playerPosition.x = 0;
        if (playerPosition.x > screenWidth - playerWidth) playerPosition.x = screenWidth - playerWidth;

        // ball movement
        ballPosition.x += ballVelocity.x * dt;
        ballPosition.y += ballVelocity.y * dt;

        // collision with walls left and right
        if (ballPosition.x - ballRadius <= 0) {
            ballPosition.x = ballRadius;
            ballVelocity.x *= -1;
        } else if (ballPosition.x + ballRadius >= screenWidth) {
            ballPosition.x = screenWidth - ballRadius;
            ballVelocity.x *= -1;
        }

        // collision with top wall
        if (ballPosition.y - ballRadius <= 0) {
            ballPosition.y = ballRadius;
            ballVelocity.y *= -1;
        }

        // collision with player / paddle
        Rectangle paddleRec = {
            playerPosition.x,
            playerPosition.y,
            static_cast<float>(playerWidth),
            static_cast<float>(playerHeight)
        };

        // collision with paddle: only when moving downwards (positive y velocity)
        if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleRec) && ballVelocity.y > 0) {
            // place ball above paddle to avoid multiple collisions
            ballPosition.y = playerPosition.y - ballRadius;
            // invert y direction
            ballVelocity.y *= -1;

            // compute hit normalized value (-1 left .. 0 center .. +1 right)
            float hitNorm = ((ballPosition.x - (playerPosition.x + playerWidth * 0.5f)) / (playerWidth * 0.5f));
            // increase x velocity based on hit position (add lateral impulse)
            ballVelocity.x += hitNorm * 200.0f;
        }

        // reset if ball falls below screen
        if (ballPosition.y - ballRadius > screenHeight) {
            ballPosition = { static_cast<float>(screenWidth)/2, static_cast<float>(screenHeight)/2 };
            ballVelocity = { 200.0f, 200.0f };
        }

        // drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawCircleV(ballPosition, 10, RED);

            DrawRectangle(
                static_cast<int>(playerPosition.x),
                static_cast<int>(playerPosition.y),
                playerWidth,
                playerHeight,
                BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}