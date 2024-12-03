#include "bar.h"

void InitBar(Bar *bar, float x, float y, float width, float height, float velocity, Color color)
{
    bar->position = (Vector2){x, y};
    bar->area = (Vector2){width, height};
    bar->color = color;
    bar->velocity = velocity;
}

void DrawBar(const Bar *bar)
{
    DrawRectangleV(bar->position, bar->area, bar->color);
}

void HandleBarControls(Bar *bar, int screenWidth)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        UpdateBarPosition(bar, 1, screenWidth);
    }

    if (IsKeyDown(KEY_LEFT) && bar->position.x > 0.0f)
    {
        UpdateBarPosition(bar, 0, screenWidth);
    }
}

void UpdateBarPosition(Bar *bar, int dir, int screenWidth)
{
    if (dir == 1 && (bar->position.x + bar->area.x) < (float)screenWidth)
    {
        bar->position.x += bar->velocity;
    }

    else if (dir == 0 && bar->position.x > 0.0f)
    {
        bar->position.x -= bar->velocity;
    }
}
