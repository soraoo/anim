#pragma once

#include <cmath>
#include <utility>

#include "vec3.h"
#include "vec4.h"

constexpr float MAT4_EPSILON = 1e-6f;

struct Mat4 {
    union {
        struct {
            float m00;
            float m10;
            float m20;
            float m30;
            float m01;
            float m11;
            float m21;
            float m31;
            float m02;
            float m12;
            float m22;
            float m32;
            float m03;
            float m13;
            float m23;
            float m33;
        };
        struct {
            Vec4 x;
            Vec4 y;
            Vec4 z;
            Vec4 t;
        };
        float v[16];
    };

    Mat4()
        : m00{1.0f}, m10{0.0f}, m20{0.0f}, m30{0.0f}, m01{0.0f}, m11{1.0f},
          m21{0.0f}, m31{0.0f}, m02{0.0f}, m12{0.0f}, m22{1.0f}, m32{0.0f},
          m03{0.0f}, m13{0.0f}, m23{0.0f}, m33{1.0f} {}
    Mat4(float m00, float m10, float m20, float m30, float m01, float m11,
         float m21, float m31, float m02, float m12, float m22, float m32,
         float m03, float m13, float m23, float m33)
        : m00{m00}, m10{m10}, m20{m20}, m30{m30}, m01{m01}, m11{m11}, m21{m21},
          m31{m31}, m02{m02}, m12{m12}, m22{m22}, m32{m32}, m03{m03}, m13{m13},
          m23{m23}, m33{m33} {}
    Mat4(float* v)
        : m00{v[0]}, m10{v[1]}, m20{v[2]}, m30{v[3]}, m01{v[4]}, m11{v[5]},
          m21{v[6]}, m31{v[7]}, m02{v[8]}, m12{v[9]}, m22{v[10]}, m32{v[11]},
          m03{v[12]}, m13{v[13]}, m23{v[14]}, m33{v[15]} {}

    Mat4& operator*=(float v) {
        m00 *= v;
        m10 *= v;
        m20 *= v;
        m30 *= v;
        m01 *= v;
        m11 *= v;
        m21 *= v;
        m31 *= v;
        m02 *= v;
        m12 *= v;
        m22 *= v;
        m32 *= v;
        m03 *= v;
        m13 *= v;
        m23 *= v;
        m33 *= v;
        return *this;
    }
};

inline bool operator==(const Mat4& lhs, const Mat4& rhs) {
    for (int i = 0; i < 16; ++i) {
        if (std::abs(lhs.v[i] - rhs.v[i]) > MAT4_EPSILON) {
            return false;
        }
    }
    return true;
}

inline bool operator!=(const Mat4& lhs, const Mat4& rhs) {
    return !(lhs == rhs);
}

inline Mat4 operator+(const Mat4& lhs, const Mat4& rhs) {
    return Mat4(lhs.m00 + rhs.m00, lhs.m10 + rhs.m10, lhs.m20 + rhs.m20,
                lhs.m30 + rhs.m30, lhs.m01 + rhs.m01, lhs.m11 + rhs.m11,
                lhs.m21 + rhs.m21, lhs.m31 + rhs.m31, lhs.m02 + rhs.m02,
                lhs.m12 + rhs.m12, lhs.m22 + rhs.m22, lhs.m32 + rhs.m32,
                lhs.m03 + rhs.m03, lhs.m13 + rhs.m13, lhs.m23 + rhs.m23,
                lhs.m33 + rhs.m33);
}

inline Mat4 operator-(const Mat4& lhs, const Mat4& rhs) {
    return Mat4(lhs.m00 - rhs.m00, lhs.m10 - rhs.m10, lhs.m20 - rhs.m20,
                lhs.m30 - rhs.m30, lhs.m01 - rhs.m01, lhs.m11 - rhs.m11,
                lhs.m21 - rhs.m21, lhs.m31 - rhs.m31, lhs.m02 - rhs.m02,
                lhs.m12 - rhs.m12, lhs.m22 - rhs.m22, lhs.m32 - rhs.m32,
                lhs.m03 - rhs.m03, lhs.m13 - rhs.m13, lhs.m23 - rhs.m23,
                lhs.m33 - rhs.m33);
}

inline Mat4 operator*(const Mat4& m, float v) {
    return Mat4(m.m00 * v, m.m10 * v, m.m20 * v, m.m30 * v, m.m01 * v,
                m.m11 * v, m.m21 * v, m.m31 * v, m.m02 * v, m.m12 * v,
                m.m22 * v, m.m32 * v, m.m03 * v, m.m13 * v, m.m23 * v,
                m.m33 * v);
}

inline Mat4 operator/(const Mat4& m, float v) { return m * (1.0f / v); }

inline Mat4 operator-(const Mat4& m) {
    return Mat4(-m.m00, -m.m10, -m.m20, -m.m30, -m.m01, -m.m11, -m.m21, -m.m31,
                -m.m02, -m.m12, -m.m22, -m.m32, -m.m03, -m.m13, -m.m23, -m.m33);
}

#define M4D(l_row, r_col)                                                      \
    lhs.v[4 * 0 + l_row] * rhs.v[4 * r_col + 0] +                              \
        lhs.v[4 * 1 + l_row] * rhs.v[4 * r_col + 1] +                          \
        lhs.v[4 * 2 + l_row] * rhs.v[4 * r_col + 2] +                          \
        lhs.v[4 * 3 + l_row] * rhs.v[4 * r_col + 3]

inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs) {

    return Mat4(M4D(0, 0), M4D(1, 0), M4D(2, 0), M4D(3, 0), M4D(0, 1),
                M4D(1, 1), M4D(2, 1), M4D(3, 1), M4D(0, 2), M4D(1, 2),
                M4D(2, 2), M4D(3, 2), M4D(0, 3), M4D(1, 3), M4D(2, 3),
                M4D(3, 3));
}

#define M4V4D(m_row, x, y, z, w)                                               \
    m.v[4 * 0 + m_row] * x + m.v[4 * 1 + m_row] * y + m.v[4 * 2 + m_row] * z + \
        m.v[4 * 3 + m_row] * w

inline Vec4 operator*(const Mat4& m, const Vec4& v) {
    return Vec4(M4V4D(0, v.x, v.y, v.z, v.w), M4V4D(1, v.x, v.y, v.z, v.w),
                M4V4D(2, v.x, v.y, v.z, v.w), M4V4D(3, v.x, v.y, v.z, v.w));
}

inline Vec3 transform_vector(const Mat4& m, const Vec3& v) {
    return Vec3(M4V4D(0, v.x, v.y, v.z, 0.0f), M4V4D(1, v.x, v.y, v.z, 0.0f),
                M4V4D(2, v.x, v.y, v.z, 0.0f));
}

inline Vec3 transform_point(const Mat4& m, const Vec3& v) {
    return Vec3(M4V4D(0, v.x, v.y, v.z, 1.0f), M4V4D(1, v.x, v.y, v.z, 1.0f),
                M4V4D(2, v.x, v.y, v.z, 1.0f));
}

inline Vec3 transform_point(const Mat4& m, const Vec3& v, float& w) {
    float tw = w;
    w = M4V4D(3, v.x, v.y, v.z, tw);
    return Vec3(M4V4D(0, v.x, v.y, v.z, tw), M4V4D(1, v.x, v.y, v.z, tw),
                M4V4D(2, v.x, v.y, v.z, tw));
}

inline void transpose(Mat4& m) {
    std::swap(m.m01, m.m10);
    std::swap(m.m02, m.m20);
    std::swap(m.m03, m.m30);
    std::swap(m.m12, m.m21);
    std::swap(m.m13, m.m31);
    std::swap(m.m23, m.m32);
}

inline Mat4 transposed(const Mat4& m) {
    return Mat4(m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20,
                m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33);
}

#define M4_3X3MINOR(m, c0, c1, c2, r0, r1, r2)                                 \
    (m[4 * c0 + r0] *                                                          \
         (m[4 * c1 + r1] * m[4 * c2 + r2] - m[4 * c1 + r2] * m[4 * c2 + r1]) - \
     m[4 * c1 + r0] *                                                          \
         (m[4 * c0 + r1] * m[4 * c2 + r2] - m[4 * c0 + r2] * m[4 * c2 + r1]) + \
     m[4 * c2 + r0] *                                                          \
         (m[4 * c0 + r1] * m[4 * c1 + r2] - m[4 * c0 + r2] * m[4 * c1 + r1]))

inline float determinant(const Mat4& m) {
    return m.v[0] * M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3) -
           m.v[4] * M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3) +
           m.v[8] * M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3) -
           m.v[12] * M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
}

inline Mat4 adjugate(const Mat4& m) {
    Mat4 cofactor(
        M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3), M4_3X3MINOR(m.v, 1, 2, 3, 0, 2, 3),
        M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 3), M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 2),
        M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3), M4_3X3MINOR(m.v, 0, 2, 3, 0, 2, 3),
        M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 3), M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 2),
        M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3), M4_3X3MINOR(m.v, 0, 1, 3, 0, 2, 3),
        M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 3), M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 2),
        M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3), M4_3X3MINOR(m.v, 0, 1, 2, 0, 2, 3),
        M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 3), M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 2));
    transpose(cofactor);
    return cofactor;
}

inline Mat4 inverse(const Mat4& m) {
    float det = determinant(m);
    if (det == 0.0f) {
        return Mat4();
    }
    return adjugate(m) * (1.0f / det);
}

inline void invert(Mat4& m) {
    float det = determinant(m);
    if (det == 0.0f) {
        m = Mat4();
        return;
    }
    m = adjugate(m) * (1.0f / det);
}

inline Mat4 frustum(float l, float r, float b, float t, float n, float f) {
    if (l == r || t == b || n == f) {
        return Mat4();
    }

    return Mat4((2.0f * n) / (r - 1.0f), 0, 0, 0, 0.0f, (2.0f * n) / (t - b),
                0.0f, 0.0f, (r + 1.0f) / (r - 1.0f), (t + b) / (t - b),
                (-(f + n)) / (f - n), -1.0f, 0.0f, 0.0f,
                (-2.0f * f * n) / (f - n), 0.0f);
}

inline Mat4 perspective(float fov, float aspect, float n, float f) {
    float max_y = n * std::tan(fov * (3.14159265359f / 360.0f));
    float max_x = max_y * aspect;
    return frustum(-max_x, max_x, -max_y, max_y, n, f);
}

inline Mat4 ortho(float l, float r, float b, float t, float n, float f) {
    if (l == r || t == b || n == f) {
        return Mat4();
    }

    return Mat4(2.0f / (r - l), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f / (t - b), 0.0f,
                0.0f, 0.0f, 0.0f, -2.0f / (f - n), 0.0f, -((r + l) / (r - l)),
                -((t + b) / (t - b)), -((f + n) / (f - n)), 1.0f);
}

inline Mat4 look_at(const Vec3& position, const Vec3& target, const Vec3& up) {
    Vec3 f = -normalized(target - position);
    Vec3 r = cross(up, f);
    if (r == Vec3()) {
        return Mat4();
    }

    normalize(r);
    Vec3 u = normalized(cross(f, r));
    Vec3 t(-dot(r, position), -dot(u, position), -dot(f, position));
    return Mat4(r.x, u.x, f.x, 0.0f, r.y, u.y, f.y, 0.0f, r.z, u.z, f.z, 0.0f,
                t.x, t.y, t.z, 1.0f);
}
