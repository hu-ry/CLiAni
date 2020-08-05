//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_HUMATH_H
#define CLIANIMATION_HUMATH_H

#include <cmath>

namespace humath {

    typedef struct __v2f{
        union{float x, r;};
        union{float y, g;};
        __v2f(__v2f const& v) : x(v.x), y(v.y){}
        __v2f(float x, float y) : x(x), y(y){}
    }v2f;

    typedef struct __v3f{
        union{float x, r;};
        union{float y, g;};
        union{float z, b;};
        __v3f(__v3f const& v) : x(v.x), y(v.y), z(v.z){}
        __v3f(float x, float y, float z) : x(x), y(y), z(z){}
    }v3f;

    typedef struct __v4f{
        union{float x, r;};
        union{float y, g;};
        union{float z, b;};
        union{float w, a;};
        __v4f(__v4f const& v) : x(v.x), y(v.y), z(v.z), w(v.w){}
        __v4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
    }v4f;

    typedef struct __mat3f{
        v3f values[3];
        __mat3f(__mat3f const& m)
                : values{
                v3f(m.values[0]),
                v3f(m.values[1]),
                v3f(m.values[2])
        } {}
        __mat3f(float s)
                : values{
                v3f(s, .0, .0),
                v3f(.0, s, .0),
                v3f(.0, .0, s)
        } {}
        __mat3f()
                : values{
                v3f(1.0, .0, .0),
                v3f(.0, 1.0, .0),
                v3f(.0, .0, 1.0)
        } {}
    }mat3f;

    typedef struct __mat4f{
        v4f values[4];
        __mat4f(__mat4f const& m)
        : values{
            v4f(m.values[0]),
            v4f(m.values[1]),
            v4f(m.values[2]),
            v4f(m.values[3])
        } {}
        __mat4f(float s)
        : values{
            v4f(s, .0, .0, .0),
            v4f(.0, s, .0, .0),
            v4f(.0, .0, s, .0),
            v4f(.0, .0, .0, s)
        } {}
        __mat4f()
                : values{
                v4f(1.0, .0, .0, .0),
                v4f(.0, 1.0, .0, .0),
                v4f(.0, .0, 1.0, .0),
                v4f(.0, .0, .0, 1.0)
        } {}
    }mat4f;

}; // end of namespace humath

#define linear_inpo(a0, a1, w) ((a0) + (w)*((a1) - (a0)))

inline double cosine_interpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * .5;

    return (a * (1 - f) + b * f);
}

inline double smooth(double t) {
    return (((6*t*t*t*t*t) - (15*t*t*t*t)) + (10*t*t*t));
}

inline double dot_prod(double x1, double y1, double x2, double y2) {
    return x1*x2+y1*y2;
}

inline float smoothstep(float edge0, float edge1, float x) {
    // Scale, bias and saturate x to 0..1 range
    x = 0.0 > (x - edge0) / (edge1 - edge0) ? 0.0 : x;
    x = 1.0 < (x - edge0) / (edge1 - edge0) ? 1.0 : x;
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

inline float sqrt_aprox(float base) {
    int i;
    float x, y;
    x = base * 0.5;
    y = base;
    i = * (int * ) &y;
    i = 0x5f3759df - (i >> 1);
    y = * ( float * ) &i;
    y = y * (1.5 - (x * y * y));
    y = y * (1.5 - (x * y * y));
    return base * y;
}
#pragma GCC diagnostic pop

#endif //CLIANIMATION_HUMATH_H
