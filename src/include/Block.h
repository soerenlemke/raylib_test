//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_BLOCK_H
#define RAYLIB_TEST_BLOCK_H
#include <functional>
#include <raylib.h>


class Block {
public:
    explicit Block(Vector2 pos, int w = 60, int h = 20);
    void Draw(Color color) const;
    void Destroy();
    [[nodiscard]] bool IsAlive() const { return alive; }
    [[nodiscard]] Rectangle GetRect() const;

    void SetOnDestroyed(std::function<void()> cb) { onDestroyed = std::move(cb); }

private:
    Vector2 position{};
    int width;
    int height;
    bool alive{true};
    std::function<void()> onDestroyed;
};


#endif // RAYLIB_TEST_BLOCK_H
