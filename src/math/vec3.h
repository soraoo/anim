#pragma once

constexpr float VEC3_EPSILON{1e-6f};

struct Vec3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float v[3];
    };

    Vec3() : x{0.0f}, y{0.0f}, z{0.0f} {}
    Vec3(float x, float y, float z) : x{x}, y{y}, z{z} {}
    Vec3(float* v) : x{v[0]}, y{v[1]}, z{v[2]} {}
};

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
