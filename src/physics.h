#ifndef ORBITRA_PHYSICS_H
#define ORBITRA_PHYSICS_H

#include "common.h"

enum class CollisionType : u8 {
    Rect = 0,
    Circle
};

struct MovingBody {
    Vector2 pos { 0.f, 0.f };
    Vector2 vel { 0.f, 0.f };
    struct Collision {
        CollisionType type { CollisionType::Rect };
        Vector2 offset { 0.f, 0.f };
        union {
            struct {
                f32 w, h;
            } box { 10.f, 10.f };
            f32 circ;
        };
    } coll;
};

bool phys_collision_aabb(MovingBody& a, MovingBody& b);
Vector2 phys_collision_aabb_side(MovingBody& a, MovingBody& b);

#endif
