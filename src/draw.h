#ifndef ORBITRA_DRAW_H
#define ORBITRA_DRAW_H

#include "common.h"
#include "raylib.h"

#define VIEWPORT_W 320
#define VIEWPORT_H 240
#define VIEWPORT_R 1.33333333333333f

struct Viewport {
    RenderTexture rtex;
    Rectangle projection;
};

Rectangle CalculateViewProjection(u16 window_width, u16 window_height);
void InitViewport(u16 window_width, u16 window_height);
void BeginViewport();
void EndViewport();
void DrawViewport();

extern Viewport viewport;

#endif
