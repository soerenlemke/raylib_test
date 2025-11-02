#include <iostream>
#include "raylib.h"

int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib-test");

    Vector2 ballPosition = {
        (float)screenWidth/2,
        (float)screenHeight/2
    };

    SetTargetFPS(60);

    // main game loop
    while (!WindowShouldClose()) {
        // key inputs
        if (IsKeyDown(KEY_D)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_A)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_W)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_S)) ballPosition.y += 2.0f;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, raylib!", 190, 200, 20, LIGHTGRAY);
            DrawCircleV(ballPosition, 50, MAROON);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}