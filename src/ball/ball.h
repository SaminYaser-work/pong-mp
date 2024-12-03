#pragma once

#ifndef BALL_H
#define BALL_H

#include "raylib.h"

// Ball structure definition
typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    int hit;
} Ball;

// Function prototypes for ball operations
void InitBall(Ball *ball, float x, float y, float vx, float vy, float radius, Color color);
void UpdateBall(Ball *ball);
void DrawBall(const Ball *ball);
void HandleBallCollisionWithWall(Ball *ball, int screenWidth, int screenHeight);

#endif // BALL_H