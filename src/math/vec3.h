#pragma once

#include <cmath>

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

    Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vec3& operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Vec3& operator/=(float rhs) { return *this *= (1.0f / rhs); }
};

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline Vec3 operator*(const Vec3& lhs, float rhs) {
    return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline Vec3 operator/(const Vec3& lhs, float rhs) { return lhs * (1.0f / rhs); }

inline Vec3 operator-(const Vec3& v) { return Vec3(-v.x, -v.y, -v.z); }

inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
    return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

inline float dot(const Vec3& v1, const Vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float len_sq(const Vec3& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

inline float len(const Vec3& v) {
    float len_sq = ::len_sq(v);
    if (len_sq < VEC3_EPSILON) {
        return 0.0f;
    }

    return std::sqrt(len_sq);
}

inline void normalize(Vec3& v) {
    float len_sq = ::len_sq(v);
    if (len_sq < VEC3_EPSILON) {
        return;
    }

    float inv_len = 1.0f / std::sqrt(len_sq);
    v *= inv_len;
}

inline Vec3 normalized(const Vec3& v) {
    float len_sq = ::len_sq(v);
    if (len_sq < VEC3_EPSILON) {
        return v;
    }

    float inv_len = 1.0f / std::sqrt(len_sq);
    return v * inv_len;
}

inline float angle(const Vec3& v1, const Vec3& v2) {
    float len_sq_v1 = len_sq(v1);
    float len_sq_v2 = len_sq(v2);
    if (len_sq_v1 < VEC3_EPSILON || len_sq_v2 < VEC3_EPSILON) {
        return 0.0f;
    }

    return std::acos(dot(v1, v2) / std::sqrt(len_sq_v1) * std::sqrt(len_sq_v2));
}

inline Vec3 project(const Vec3& v1, const Vec3& v2) {
    float len_v2 = len(v2);
    if (len_v2 < VEC3_EPSILON) {
        return Vec3();
    }

    float scale = dot(v1, v2) / len_v2;
    return v2 * scale;
}

inline Vec3 reject(const Vec3& v1, const Vec3& v2) {
    Vec3 projection = project(v1, v2);
    return v1 - projection;
}

inline Vec3 reflect(const Vec3& v1, const Vec3& v2) {
    Vec3 proj = project(v1, v2);
    return v1 - proj * 2.0f;
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

inline Vec3 lerp(const Vec3& v1, const Vec3& v2, float t) {
    return Vec3(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t,
                v1.z + (v2.z - v1.z) * t);
}

inline Vec3 nlerp(const Vec3& v1, const Vec3& v2, float t) {
    return normalized(lerp(v1, v2, t));
}

inline Vec3 slerp(const Vec3& v1, const Vec3& v2, float t) {
    Vec3 from = normalized(v1);
    Vec3 to = normalized(v2);

    float cos = dot(from, to);
    if (cos > 1.0f - VEC3_EPSILON) {
        return nlerp(v1, v2, t);
    }

    float theta = angle(from, to);
    float sin_theta = std::sin(theta);

    float a = std::sin((1.0f - t) * theta) / sin_theta;
    float b = std::sin(t * theta) / sin_theta;

    return from * a + to * b;
}

inline bool operator==(const Vec3& lhs, const Vec3& rhs) {
    Vec3 diff(lhs - rhs);
    return len_sq(diff) < VEC3_EPSILON;
}

inline bool operator!=(const Vec3& lhs, const Vec3& rhs) {
    return !(lhs == rhs);
}
