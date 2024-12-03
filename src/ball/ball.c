#include "ball.h"

void InitBall(Ball *ball, float x, float y, float vx, float vy, float radius, Color color)
{
    ball->position = (Vector2){x, y};
    ball->velocity = (Vector2){vx, vy}; // Initial velocity
    ball->radius = radius;
    ball->color = color;
    ball->hit = 0;
}

void UpdateBall(Ball *ball)
{
    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;
}

void DrawBall(const Ball *ball)
{
    DrawCircleV(ball->position, ball->radius, ball->color);
}

void HandleBallCollisionWithWall(Ball *ball, int screenWidth, int screenHeight)
{
    if (ball->position.x - ball->radius <= 0 ||
        ball->position.x + ball->radius >= screenWidth)
    {
        ball->velocity.x *= -1;
    }

    if (ball->position.y - ball->radius <= 0) {
        ball->hit = 1;
    } else if (ball->position.y + ball->radius >= screenHeight) {
        ball->hit = 2;
    }
}
