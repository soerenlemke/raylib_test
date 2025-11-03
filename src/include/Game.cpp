//
// Created by soeren on 02.11.25.
//

#include "../include/Game.h"

#include <string>

#include "Block.h"

Game::Game(const int screenWidth, const int screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      paddle({static_cast<float>(screenWidth) / 2 - 50.0f, static_cast<float>(screenHeight) - 30.0f}),
      ball({static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2}) {
}

int Game::Run() {
    InitWindow(screenWidth, screenHeight, "raylib-test");
    SetTargetFPS(120);

    BuildBlocks(5, 10, 70, 25, 5);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();
        Update(dt);

        BeginDrawing();
        Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void Game::Update(const float dt) {
    paddle.Update(dt, screenWidth);
    ball.Update(dt);

    physics.Update(ball, paddle, blocks, screenWidth, screenHeight);
}


void Game::Draw() const {
    ClearBackground(RAYWHITE);
    DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 10, 20, DARKGRAY);

    ball.Draw(RED);
    paddle.Draw(GRAY);

    DrawBlocks();
}

void Game::BuildBlocks(int rows, int cols, int blockWidth, int blockHeight, int spacing) {
    blocks.clear();
    const auto totalWidth = static_cast<float>(cols * blockWidth + (cols - 1) * spacing);
    const auto startX = (static_cast<float>(screenWidth) - totalWidth) * 0.5f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            constexpr auto startY = 50.0f;
            blocks.emplace_back(
                Vector2{
                    startX + static_cast<float>(col * (blockWidth + spacing)),
                    startY + static_cast<float>(row * (blockHeight + spacing))
                },
                blockWidth,
                blockHeight
            );
        }
    }
}

void Game::DrawBlocks() const {
    for (const auto &block: blocks) {
        if (block.IsAlive()) block.Draw(BLUE);
    }
}
