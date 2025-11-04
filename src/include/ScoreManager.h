//
// Created by soeren on 04.11.25.
//

#ifndef RAYLIB_TEST_SCOREMANAGER_H
#define RAYLIB_TEST_SCOREMANAGER_H


class Block;
class ScoreManager {
public:
    ScoreManager() = default;

    void SetStartingCount(int count) { startingBlocks = count; }
    void Reset() {
        startingBlocks = 0;
        score = 0;
    }

    void SubscribeToBlock(Block &block);
    void OnBlockDestroyed();

    [[nodiscard]] int GetScore() const { return score; }

private:
    int startingBlocks = 0;
    int score = 0;
};


#endif // RAYLIB_TEST_SCOREMANAGER_H
