#pragma once

#ifndef BAR_H
#define BAR_H

#include "raylib.h"

// Bar structure definition
typedef struct
{
    Vector2 position;
    Vector2 area;
    float velocity;
    Color color;
} Bar;

// Function prototypes for bar operations

void InitBar(Bar *bar, float x, float y, float width, float height, float velocity, Color color);
void DrawBar(const Bar *bar);
void HandleBarControls(Bar *bar, int screenWidth);
void UpdateBarPosition(Bar *bar, int dir, int screenWidth);

#endif // BAR_H