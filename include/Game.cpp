//
// Created by soeren on 02.11.25.
//

#include "Game.h"

#include <string>

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      paddle({static_cast<float>(screenWidth) / 2 - 50, static_cast<float>(screenHeight) - 30}),
      ball({static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2}) {
}

int Game::Run() {
    InitWindow(screenWidth, screenHeight, "raylib-test");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Update(dt);

        BeginDrawing();
        Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void Game::Update(float dt) {
    paddle.Update(dt, screenWidth);
    ball.Update(dt);

    // wall collisions
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

    // paddle collision (only if moving downward)
    Rectangle pad = paddle.GetRect();
    if (CheckCollisionCircleRec(ball.GetPosition(), ball.GetRadius(), pad) && ball.GetVelocity().y > 0) {
        Vector2 p = ball.GetPosition();
        p.y = pad.y - ball.GetRadius();
        Vector2 v = ball.GetVelocity();
        v.y *= -1;

        float hitNorm = ((p.x - (pad.x + pad.width * 0.5f)) / (pad.width * 0.5f));
        v.x += hitNorm * 200.0f; // increase lateral velocity based on hit position

        ball.Reset(p, v);
    }

    // reset if ball fell below screen
    if (ball.GetPosition().y - ball.GetRadius() > static_cast<float>(screenHeight)) {
        ball.Reset(Vector2{static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f},
                   Vector2{200.0f, 200.0f});
    }
}

void Game::Draw() {
    ClearBackground(RAYWHITE);
    DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 10, 20, DARKGRAY);

    ball.Draw(RED);
    paddle.Draw(GRAY);
}
