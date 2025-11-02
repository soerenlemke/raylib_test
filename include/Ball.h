//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_BALL_H
#define RAYLIB_TEST_BALL_H
#include <raylib.h>


class Ball {
public:
    Ball(float radius, Vector2 pos, Vector2 vel);

    void Update(float dt);

    void Draw(Color color) const;

    void Reset(Vector2 pos, Vector2 vel);

    Vector2 GetPosition() const { return position; }
    Vector2 GetVelocity() const { return velocity; }
    void SetVelocity(const Vector2 &v) { velocity = v; }
    float GetRadius() const { return radius; }

private:
    Vector2 position;
    Vector2 velocity;
    float radius;
};


#endif //RAYLIB_TEST_BALL_H
