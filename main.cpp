#include <iostream>
#include "raylib.h"

int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    constexpr int playerHeight = 30;
    constexpr int playerWidth = 100;

    InitWindow(screenWidth, screenHeight, "raylib-test");

    Vector2 playerPosition = {
        static_cast<float>(screenWidth)/2-static_cast<float>(playerWidth)/2,
        static_cast<float>(screenHeight)-playerHeight
    };

    SetTargetFPS(60);

    // main game loop
    while (!WindowShouldClose()) {
        // key inputs
        if (IsKeyDown(KEY_D)) playerPosition.x += 3.0f;
        if (IsKeyDown(KEY_A)) playerPosition.x -= 3.0f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

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