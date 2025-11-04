//
// Created by soeren on 02.11.25.
//

#ifndef RAYLIB_TEST_BALL_H
#define RAYLIB_TEST_BALL_H
#include <raylib.h>


class Ball {
public:
    explicit Ball(Vector2 pos, float radius = 10.0f, Vector2 vel = {200.0f, -200.0f});

    void Update(float dt);

    void Draw(Color color) const;

    void Respawn(Vector2 pos);

    [[nodiscard]] Vector2 GetPosition() const { return position; }
    [[nodiscard]] Vector2 GetVelocity() const { return velocity; }
    void SetVelocity(const Vector2 &v) { velocity = v; }
    void SetPosition(const Vector2 &p) { position = p; }
    [[nodiscard]] float GetRadius() const { return radius; }

private:
    Vector2 position{};
    Vector2 velocity{};
    float radius;
};


#endif // RAYLIB_TEST_BALL_H
