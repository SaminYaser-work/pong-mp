#include "ball/ball.h"
#include "bar/bar.h"
#include "raylib.h"
#include "resource_dir.h"
#include "time.h"
#include <stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGTH 800

void BallWithBarCollision(Ball *ball, Bar *bar);
void UpdateAIPosition(Ball *ball, Bar *bar);
void checkWin(Ball *ball);

int hits = 0;

int main()
{

	srand(time(NULL));

	// config
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Pong");
	SearchAndSetResourceDir("resources");
	SetTargetFPS(170);

	// ball
	Ball ball;
	InitBall(&ball, (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGTH / 2, 2.0f, 2.0f, 10, WHITE);

	// Bar
	Bar bar;
	InitBar(&bar, (float)SCREEN_WIDTH / 2, 750.0f, 100, 10, 5, YELLOW);

	// Bar 2
	Bar bar2;
	InitBar(&bar2, (float)SCREEN_WIDTH / 2, 50.0f, 100, 10, 5, BLUE);

	// game loop
	while (!WindowShouldClose())
	{
		UpdateBall(&ball);
		HandleBallCollisionWithWall(&ball, SCREEN_WIDTH, SCREEN_HEIGTH);

		UpdateAIPosition(&ball, &bar2);
		HandleBarControls(&bar, SCREEN_WIDTH);

		BallWithBarCollision(&ball, &bar);
		BallWithBarCollision(&ball, &bar2);

		BeginDrawing();
		ClearBackground(BLACK);

		DrawBall(&ball);
		DrawBar(&bar);
		DrawBar(&bar2);

		checkWin(&ball);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void increaseDifficulty(Ball *ball, double *time)
{
	double currTime = GetTime();
	if (currTime - *time > 10)
	{
		ball->velocity.x += 1.0F;
		ball->velocity.y += 1.0F;
		*time = currTime;
	}
}

void BallWithBarCollision(Ball *ball, Bar *bar)
{
	bool isColliding = CheckCollisionCircleRec(
		ball->position,
		ball->radius,
		(Rectangle){bar->position.x, bar->position.y, bar->area.x, bar->area.y});

	if (isColliding)
	{
		ball->velocity.y *= -1;

		if (hits++ > 3)
		{
			ball->velocity.x += 0.5F;
			ball->velocity.y += 0.5F;
			hits = 0;
		}
	}
}

void UpdateAIPosition(Ball *ball, Bar *bar)
{
	if (ball->position.x - bar->area.x / 2 > bar->position.x)
	{
		UpdateBarPosition(bar, 1, SCREEN_WIDTH);
	}
	else
	{
		UpdateBarPosition(bar, 0, SCREEN_WIDTH);
	}
}

void checkWin(Ball *ball)
{
	if (ball->hit != 0)
	{
		ball->position.x = (float)SCREEN_WIDTH / 2;
		ball->position.y = (float)SCREEN_HEIGTH / 2;
		ball->velocity.x = ((rand() & 1) == 0) ? 2.0f : -2.0f;
		ball->velocity.y = ((rand() & 1) == 0) ? 2.0f : -2.0f;
		ball->hit = 0;
	}
}