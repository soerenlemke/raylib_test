//
// Created by soeren on 03.11.25.
//

#ifndef RAYLIB_TEST_PHYSICS_H
#define RAYLIB_TEST_PHYSICS_H
#include <vector>


class Block;
class Paddle;
class Ball;

class Physics {
public:
    static void Update(Ball &ball, const Paddle &paddle, std::vector<Block> &blocks, int screenWidth, int screenHeight);


private:
    static void CheckBallCollisionsWithWalls(Ball &ball, int screenWidth);
    static void CheckBallCollisionsWithPaddle(Ball &ball, const Paddle &paddle);
    static void CheckBallCollisionsWithBlocks(Ball &ball, std::vector<Block> &blocks);
    static void CheckBallOffscreen(Ball &ball, int screenWidth, int screenHeight);
    static void ClearDeadBlocks(std::vector<Block> &blocks);
};


#endif // RAYLIB_TEST_PHYSICS_H
