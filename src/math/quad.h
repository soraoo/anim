#pragma once

#include <cmath>

#include "mat4.h"
#include "vec3.h"

constexpr float QUAT_EPSILON = 1e-6f;

struct Quat {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        struct {
            Vec3 vector;
            float scalar;
        };
        float v[4];
    };

    Quat() : x{0.0f}, y{0.0f}, z{0.0f}, w{1.0f} {}
    Quat(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}
};

inline Quat operator+(const Quat& lhs, const Quat& rhs) {
    return Quat(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

inline Quat operator-(const Quat& lhs, const Quat& rhs) {
    return Quat(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

inline Quat operator*(const Quat& q, float v) {
    return Quat(q.x * v, q.y * v, q.z * v, q.w * v);
}

inline Quat operator-(const Quat& q) { return Quat(-q.x, -q.y, -q.z, -q.w); }

inline bool operator==(const Quat& lhs, const Quat& rhs) {
    return std::abs(lhs.x - rhs.x) <= QUAT_EPSILON &&
           std::abs(lhs.y - rhs.y) <= QUAT_EPSILON &&
           std::abs(lhs.z - rhs.z) <= QUAT_EPSILON &&
           std::abs(lhs.w - rhs.w) <= QUAT_EPSILON;
}

inline bool operator!=(const Quat& lhs, const Quat& rhs) {
    return !(lhs == rhs);
}

inline Quat angle_axis(float angle, const Vec3& axis) {
    Vec3 norm = normalized(axis);
    float s = std::sin(angle * 0.5f);
    return Quat(norm.x * s, norm.y * s, norm.z * s, std::cos(angle * 0.5f));
}

inline Quat from_to(const Vec3& from, const Vec3& to) {
    Vec3 f = normalized(from);
    Vec3 t = normalized(to);
    if (f == t) {
        return Quat();
    } else if (f == -t) {
        Vec3 ortho = Vec3(1.0f, 0.0f, 0.0f);
        if (std::abs(f.y) < std::abs(f.x)) {
            ortho = Vec3(0.0f, 1.0f, 0.0f);
        }
        if (std::abs(f.z) < std::abs(f.y) && std::abs(f.z) < std::abs(f.x)) {
            ortho = Vec3(0.0f, 0.0f, 1.0f);
        }
        Vec3 axis = normalized(cross(f, ortho));
        return Quat(axis.x, axis.y, axis.z, 0.0f);
    }

    Vec3 half = normalized(f + t);
    Vec3 axis = cross(f, half);
    return Quat(axis.x, axis.y, axis.z, dot(f, half));
}

inline Vec3 get_axis(const Quat& quat) { return normalized(quat.vector); }

inline float get_angle(const Quat& quat) { return 2.0f * std::acos(quat.w); }

inline bool same_orientation(const Quat& lhs, const Quat& rhs) {
    return (std::abs(lhs.x - rhs.x) <= QUAT_EPSILON &&
            std::abs(lhs.y - rhs.y) <= QUAT_EPSILON &&
            std::abs(lhs.z - rhs.z) <= QUAT_EPSILON &&
            std::abs(lhs.w - rhs.w) <= QUAT_EPSILON) ||
           (std::abs(lhs.x + rhs.x) <= QUAT_EPSILON &&
            std::abs(lhs.y + rhs.y) <= QUAT_EPSILON &&
            std::abs(lhs.z + rhs.z) <= QUAT_EPSILON &&
            std::abs(lhs.w + rhs.w) <= QUAT_EPSILON);
}

inline float dot(const Quat& q1, const Quat& q2) {
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

inline float len_sq(const Quat& q) {
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

inline float len(const Quat& q) {
    float len_sq = ::len_sq(q);
    if (len_sq < QUAT_EPSILON) {
        return 0.0f;
    }

    return std::sqrt(len_sq);
}

inline void normalize(Quat& q) {
    float len_sq = ::len_sq(q);
    if (len_sq < QUAT_EPSILON) {
        return;
    }

    float i_len = 1.0f / std::sqrt(len_sq);
    q.x *= i_len;
    q.y *= i_len;
    q.z *= i_len;
    q.w *= i_len;
}

inline Quat normalized(const Quat& q) {
    float len_sq = ::len_sq(q);
    if (len_sq < QUAT_EPSILON) {
        return Quat();
    }
    float i_len = 1.0f / std::sqrt(len_sq);
    return q * i_len;
}

inline Quat conjugate(const Quat& q) { return Quat(-q.x, -q.y, -q.z, q.w); }

inline Quat inverse(const Quat& q) {
    float len_sq = ::len_sq(q);
    if (len_sq < QUAT_EPSILON) {
        return Quat();
    }

    float i_len = 1.0f / len_sq;
    return Quat(-q.x * i_len, -q.y * i_len, -q.z * i_len, q.w * i_len);
}

inline Quat operator*(const Quat& q1, const Quat& q2) {
    return Quat(q2.x * q1.w + q2.y * q1.z - q2.z * q1.y + q2.w * q1.x,
                -q2.x * q1.z + q2.y * q1.w + q2.z * q1.x + q2.w * q1.y,
                q2.x * q1.y - q2.y * q1.x + q2.z * q1.w + q2.w * q1.z,
                -q2.x * q1.x - q2.y * q1.y - q2.z * q1.z + q2.w * q1.w);
}

inline Vec3 operator*(const Quat& q, const Vec3& v) {
    return q.vector * 2.0f * dot(q.vector, v) +
           v * (q.scalar * q.scalar - dot(q.vector, q.vector)) +
           cross(q.vector, v) * 2.0f * q.scalar;
}

inline Quat lerp(const Quat& from, const Quat& to, float t) {
    return from + (to - from) * t;
}

inline Quat nlerp(const Quat& from, const Quat& to, float t) {
    return normalized(from + (to - from) * t);
}

inline Quat operator^(const Quat& q, float v) {
    float angle = 2.0f * std::acos(q.scalar);
    Vec3 axis = normalized(q.vector);

    float half_cos = std::cos(v * angle * 0.5f);
    float half_sin = std::sin(v * angle * 0.5f);
    return Quat(axis.x * half_sin, axis.y * half_sin, axis.z * half_sin,
                half_cos);
}

inline Quat slerp(const Quat& from, const Quat& to, float t) {
    if (std::abs(dot(from, to)) > 1.0f - QUAT_EPSILON) {
        return nlerp(from, to, t);
    }

    Quat delta = inverse(from) * to;
    return normalized((delta ^ t) * from);
}

inline Quat look_rotation(const Vec3& direction, const Vec3& up) {
    Vec3 f = normalized(direction);
    Vec3 u = normalized(up);
    Vec3 r = cross(u, f);
    u = cross(f, r);

    Quat world_to_object = from_to(Vec3(0.0f, 0.0f, -1.0f), f);
    Vec3 object_up = world_to_object * Vec3(0.0f, 1.0f, 0.0f);
    Quat u2u = from_to(object_up, u);

    Quat result = world_to_object * u2u;
    return normalized(result);
}

inline Mat4 quat_to_mat4(const Quat& q) {
    Vec3 r = q * Vec3(1.0f, 0.0f, 0.0f);
    Vec3 u = q * Vec3(0.0f, 1.0f, 0.0f);
    Vec3 f = q * Vec3(0.0f, 0.0f, 1.0f);

    return Mat4(r.x, r.y, r.z, 0.0f, u.x, u.y, u.z, 0.0f, f.x, f.y, f.z, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

inline Quat mat4_to_quat(const Mat4& m) {
    Vec3 up = normalized(Vec3(m.y.x, m.y.y, m.y.z));
    Vec3 forward = normalized(Vec3(m.z.x, m.z.y, m.z.z));
    Vec3 right = cross(up, forward);
    up = cross(forward, right);
    return look_rotation(forward, up);
}
