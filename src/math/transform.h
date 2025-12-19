#pragma once

#include "mat4.h"
#include "quat.h"
#include "vec3.h"

struct Transform {
    Vec3 position;
    Quat rotation;
    Vec3 scale;

    Transform()
        : position{0.0f, 0.0f, 0.0f}, rotation{0.0f, 0.0f, 0.0f, 1.0f},
          scale{1.0f, 1.0f, 1.0f} {}
    Transform(const Vec3& pos, const Quat& rot, const Vec3& scale)
        : position{pos}, rotation{rot}, scale(scale) {}
};

inline Transform combine(const Transform& t1, const Transform& t2) {
    Vec3 scale = t1.scale * t2.scale;
    Quat rotation = t2.rotation * t1.rotation;
    Vec3 position = t1.rotation * (t1.scale * t2.position);
    position += t1.position;

    return Transform(scale, rotation, position);
}

inline Transform inverse(const Transform& t) {
    Transform inv;
    inv.rotation = inverse(t.rotation);
    inv.scale.x = std::abs(t.scale.x) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.x;
    inv.scale.y = std::abs(t.scale.y) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.y;
    inv.scale.z = std::abs(t.scale.z) < VEC3_EPSILON ? 0.0f : 1.0f / t.scale.z;
    inv.position = inv.rotation * (inv.scale * -t.position);
    return inv;
}

inline Transform mix(const Transform& from, const Transform& to, float t) {
    Quat to_rot = to.rotation;
    if (dot(from.rotation, to_rot) < 0.0f) {
        to_rot = -to_rot;
    }

    return Transform(lerp(from.position, to.position, t),
                     nlerp(from.rotation, to_rot, t),
                     lerp(from.scale, to.scale, t));
}

inline Mat4 transform_to_mat(const Transform& t) {
    Vec3 x = t.rotation * Vec3(1.0f, 0.0f, 0.0f);
    Vec3 y = t.rotation * Vec3(0.0f, 1.0f, 0.0f);
    Vec3 z = t.rotation * Vec3(0.0f, 0.0f, 1.0f);

    x *= t.scale.x;
    y *= t.scale.y;
    z *= t.scale.z;

    return Mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f,
                t.position.x, t.position.y, t.position.z, 1.0f);
}

inline Transform mat4_to_transform(const Mat4& m) {
    Transform out;

    out.position = Vec3(m.v[12], m.v[13], m.v[14]);
    out.rotation = mat4_to_quat(m);

    Mat4 rot_scale_mat(m.v[0], m.v[1], m.v[2], 0.0f, m.v[4], m.v[5], m.v[6],
                       0.0f, m.v[8], m.v[9], m.v[10], 0.0f, 0.0f, 0.0f, 0.0f,
                       1.0f);
    Mat4 inv_rot_mat = quat_to_mat4(inverse(out.rotation));
    Mat4 scale_skew_mat = rot_scale_mat * inv_rot_mat;
    out.scale =
        Vec3(scale_skew_mat.v[0], scale_skew_mat.v[5], scale_skew_mat.v[10]);
    return out;
}

inline Vec3 transform_point(const Transform& t, const Vec3& v) {
    Vec3 out = t.rotation * (t.scale * v);
    out += t.position;
    return out;
}

inline Vec3 transform_vector(const Transform& t, const Vec3& v) {
    return t.rotation * (t.scale * v);
}
