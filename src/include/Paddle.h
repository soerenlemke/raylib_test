//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_PADDLE_H
#define RAYLIB_TEST_PADDLE_H
#include <raylib.h>


class Paddle {
public:
    Paddle(Vector2 pos, int w = 100, int h = 20, float speed = 300.0f);

    void Update(float dt, int screenWidth);

    void Draw(Color color) const;

    Rectangle GetRect() const;

private:
    Vector2 position;
    int width;
    int height;
    float speed;
};


#endif // RAYLIB_TEST_PADDLE_H
