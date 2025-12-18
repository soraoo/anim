#pragma once

template <typename T>
struct TVec2 {
    union {
        struct {
            T x;
            T y;
        };
        T v[2];
    };

    TVec2() : x{0}, y{0} {}
    TVec2(T x, T y) : x{x}, y{y} {}
    TVec2(T* v) : x{v[0]}, y{v[1]} {}
};

using Vec2 = TVec2<float>;
using IVec2 = TVec2<int>;
