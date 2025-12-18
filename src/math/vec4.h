#pragma once

template <typename T>
struct TVec4 {
    union {
        struct {
            T x;
            T y;
            T z;
            T w;
        };
        T v[4];
    };

    TVec4() : x{0}, y{0}, z{0}, w{0} {}
    TVec4(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} {}
    TVec4(T* v) : x{v[0]}, y{v[1]}, z{v[2]}, w{v[3]} {}
};

using Vec4 = TVec4<float>;
using IVec4 = TVec4<int>;
using UVec4 = TVec4<unsigned int>;
