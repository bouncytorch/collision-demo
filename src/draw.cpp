#include "draw.h"
#include "common.h"
#include "raylib.h"

Viewport viewport;

Rectangle CalculateViewProjection(u16 width, u16 height) {
    f32 ratio = (f32)width / height;
    if (ratio > VIEWPORT_R) {
        u16 view_width = height * VIEWPORT_R, view_height = height;

        return {((f32)width / 2) - ((f32)view_width / 2), 0, (f32)view_width,
                (f32)view_height};
    } else {
        u16 view_width = width, view_height = width / VIEWPORT_R;

        return {0, ((f32)height / 2) - ((f32)view_height / 2), (f32)view_width,
                (f32)view_height};
    }
}

void InitViewport(u16 window_width, u16 window_height) {
    SetWindowMinSize(VIEWPORT_W, VIEWPORT_H);
    viewport = {.rtex = LoadRenderTexture(VIEWPORT_W, VIEWPORT_H),
                .projection =
                    CalculateViewProjection(window_width, window_height)};
}

void BeginViewport() {
    BeginTextureMode(viewport.rtex);
}

void EndViewport() { EndTextureMode(); }

void DrawViewport() {
    DrawTexturePro(viewport.rtex.texture,
                   {0, 0, (f32)VIEWPORT_W, -(f32)VIEWPORT_H},
                   viewport.projection, (Vector2){0, 0}, 0.0f, WHITE);
}
