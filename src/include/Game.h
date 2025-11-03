//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_GAME_H
#define RAYLIB_TEST_GAME_H
#include <vector>

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "Physics.h"


class Game {
public:
    Game(int screenWidth, int screenHeight);

    int Run();

private:
    void Update(float dt);

    void Draw() const;

    void BuildBlocks(int rows, int cols, int blockWidth, int blockHeight, int spacing);

    void DrawBlocks() const;

    int screenWidth;
    int screenHeight;
    Paddle paddle;
    Ball ball;
    std::vector<Block> blocks;
    Physics physics;
};


#endif //RAYLIB_TEST_GAME_H
