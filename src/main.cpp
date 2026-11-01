#include "common.h"
#include "config.h"
#include "draw.h"
#include "raylib.h"
#include <cmath>
#include "physics.h"

int main() {
    orb_Config config = config_init();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    if (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::VSYNC)
        SetConfigFlags(FLAG_VSYNC_HINT);
    if (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::WINDOW_FULLSCREEN)
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
    if (config.graphics.flags & CONFIG_GRAPHICS_FLAGS::WINDOW_BORDERLESS)
        SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);

    InitWindow(config.graphics.window.w, config.graphics.window.h, "collision-demo");
    SetTargetFPS(166);

    orb_Config::Graphics::Window window = { (u16) GetScreenWidth(),
                                            (u16) GetScreenHeight() };

    InitViewport(window.w, window.h);

    bool window_resizing = false;
    f32 window_resize_timer = 0;

    MovingBody a {
        .pos { 0, 0 },
        .coll {
            .box { 10, 10 }
        }
    },
    b {
        .pos { 50, 50 },
        .coll {
            .box { 20, 20 }
        }
    };

    while (!WindowShouldClose()) {
        f32 delta = GetFrameTime();

        if (IsWindowResized()) {
            window_resize_timer = 0;
            window_resizing = true;
            window = {(u16)GetScreenWidth(), (u16)GetScreenHeight()};
            config.graphics.window = window;
            viewport.projection = CalculateViewProjection(window.w, window.h);
        } else if (window_resizing) {
            window_resize_timer += delta;
            if (window_resize_timer > 2.0f) {
                window_resizing = false;
                window_resize_timer = 0;
                config_write(config);
            }
        }

        Vector2 dir = { (f32)IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
                        (f32)IsKeyDown(KEY_S) - IsKeyDown(KEY_W) };

        f32 accel = 0.995f;
        a.vel = lerp_vec2(a.vel, 200.f * dir, 1.0f - pow(1.f - accel, delta));
        Vector2 veln = lerp_vec2(a.vel, 200.f * dir, 1.0f - pow(1.f - accel, delta));
        a.pos += a.vel * delta;

        Vector2 collision = phys_collision_aabb_side(a,b);
        bool is_colliding = collision.x || collision.y;

        BeginViewport();
        ClearBackground({40,40,40,255});

        DrawRectangleLinesEx({ a.pos.x, a.pos.y, a.coll.box.w, a.coll.box.h }, 1, is_colliding ? RED : BLUE);
        DrawRectangleLinesEx({ a.pos.x + veln.x * delta, a.pos.y + veln.y * delta, a.coll.box.w, a.coll.box.h }, 1, GREEN);
        DrawRectangleLinesEx({ b.pos.x, b.pos.y, b.coll.box.w, b.coll.box.h }, 1, is_colliding ? RED : BLUE);

        // ...

        EndViewport();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawViewport();
        DrawFPS(0, 0);
        EndDrawing();
    }
}
