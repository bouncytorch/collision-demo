#include "common.h"
#include <cmath>

Vector2 operator+(const Vector2 &lv, const Vector2 &rv) {
    return Vector2{ lv.x + rv.x, lv.y + rv.y };
}

Vector2& operator+=(Vector2 &lv, const Vector2 &rv) {
    lv = lv + rv; return lv;
}

Vector2 operator-(const Vector2 &lv, const Vector2 &rv) {
    return Vector2{ lv.x - rv.x, lv.y - rv.y };
}

Vector2& operator-=(Vector2 &lv, const Vector2 &rv) {
    lv = lv - rv; return lv;
}

Vector2 operator*(const Vector2 &v, const f32 &scalar) {
    return Vector2{ v.x * scalar, v.y * scalar };
}

Vector2 operator*(const f32 &scalar, const Vector2 &v) {
    return v * scalar;
}

Vector2 operator*(const Vector2 &v1, const Vector2 &v2) {
    return { v1.x * v2.x, v1.y * v2.y };
}

Vector2& operator*=(Vector2 &lv, const Vector2 &rv) {
    lv = lv * rv; return lv;
}

f32 lerp_f(f32 a, f32 b, f32 f) { return (1 - f) * a + (b * f); }
Vector2 lerp_vec2(Vector2 a, Vector2 b, f32 f) { return (1 - f) * a + (b * f); }

Vector2 normalize_vec2(Vector2 vec) {
    float m = sqrtf(vec.x * vec.x + vec.y * vec.y);
    return { vec.x / m, vec.y / m };
}
