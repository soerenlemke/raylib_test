//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_GAME_H
#define RAYLIB_TEST_GAME_H
#include "Ball.h"
#include "Paddle.h"


class Game {
public:
    Game(int screenWidth, int screenHeight);

    int Run();

private:
    void Update(float dt);

    void Draw();

    void DrawBlocks(int rows, int cols, int blockWidth, int blockHeight, int spacing) const;

    int screenWidth;
    int screenHeight;
    Paddle paddle;
    Ball ball;
};


#endif //RAYLIB_TEST_GAME_H
