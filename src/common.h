#ifndef ORBITRA_COMMON_H
#define ORBITRA_COMMON_H

#include "raylib.h"
#include <cstddef>
#include <cstdint>
#include <filesystem> // IWYU pragma: keep
// TODO: Fix this nonsense
namespace fs = std::filesystem; // NOLINT(misc-unused-alias-decls)

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t   usize;

typedef float  f32;
typedef double f64;

Vector2  operator+(const Vector2 &lv, const Vector2 &rv);
Vector2  operator-(const Vector2 &lv, const Vector2 &rv);
Vector2  operator*(const Vector2 &v, const f32 &scalar);
Vector2  operator*(const f32 &scalar, const Vector2 &v);
Vector2  operator*(const Vector2 &v, const Vector2 &scalar);

Vector2& operator+=(Vector2 &lv, const Vector2 &rv);
Vector2& operator-=(Vector2 &lv, const Vector2 &rv);
Vector2& operator*=(Vector2 &lv, const Vector2 &rv);

f32 lerp_f(f32 a, f32 b, f32 f);
Vector2 lerp_vec2(Vector2 a, Vector2 b, f32 f);

Vector2 normalize_vec2(Vector2 vec);


enum class orb_Error: i8 {
    SUCCESS, GENERIC, FWRITE_ERROR
};

#endif
