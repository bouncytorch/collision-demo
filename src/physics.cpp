#include "physics.h"
#include "raylib.h"
#include <cmath>

Vector2 phys_collision_aabb_side(MovingBody& a, MovingBody& b) {
    f32 a_center_x = a.pos.x + a.coll.box.w * 0.5f;
    f32 a_center_y = a.pos.y + a.coll.box.h * 0.5f;
    f32 b_center_x = b.pos.x + b.coll.box.w * 0.5f;
    f32 b_center_y = b.pos.y + b.coll.box.h * 0.5f;

    f32 dx = b_center_x - a_center_x;
    f32 dy = b_center_y - a_center_y;

    f32 px = (a.coll.box.w * 0.5f + b.coll.box.w * 0.5f) - fabsf(dx);
    f32 py = (a.coll.box.h * 0.5f + b.coll.box.h * 0.5f) - fabsf(dy);

    if (px <= 0 || py <= 0)
        return { 0, 0 };
    else
        return { dx, dy };
}

bool phys_collision_aabb(MovingBody& a, MovingBody& b) {
    f32 a_right  = a.pos.x + a.coll.box.w;
    f32 a_bottom = a.pos.y + a.coll.box.h;
    f32 b_right  = b.pos.x + b.coll.box.w;
    f32 b_bottom = b.pos.y + b.coll.box.h;

    return a.pos.x  < b_right
        && a_right  > b.pos.x
        && a.pos.y  < b_bottom
        && a_bottom > b.pos.y;
}
