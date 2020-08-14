//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_HUMATH_H
#define CLIANIMATION_HUMATH_H

#include <cmath>
#include <cassert>

namespace humath {

    typedef struct v2f{
        union{float x, r;};
        union{float y, g;};
        // Implicit basic constructors
        inline constexpr v2f(v2f const& v) : x(v.x), y(v.y){}
        // Explicit basic constructors
        inline constexpr explicit v2f(float scalar) : x(scalar), y(scalar){}
        inline constexpr v2f(float x, float y) : x(x), y(y){}

        inline constexpr v2f& operator=(v2f const& v) = default;
    }v2f;

    typedef struct v3f{
        union{float x, r;};
        union{float y, g;};
        union{float z, b;};
        // Component Access
        typedef int length_t;
        static constexpr length_t length(){return 3;}
        constexpr float & operator[](length_t i) {
            assert(i >= 0 && i < this->length());
            switch(i)
            {
                default:
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
            }
        }
        constexpr float const& operator[](length_t i) const {
            assert(i >= 0 && i < this->length());
            switch(i)
            {
                default:
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
            }
        }
        // Implicit basic constructors
        inline constexpr v3f(v3f const& v) : x(v.x), y(v.y), z(v.z){}
        // Explicit basic constructors
        inline constexpr explicit v3f(float scalar) : x(scalar), y(scalar), z(scalar){}
        inline constexpr v3f(float x, float y, float z) : x(x), y(y), z(z){}
        // Unary arithmetic operators
        inline constexpr v3f& operator=(v3f const& v) = default;
        inline constexpr v3f& operator+=(float scalar) {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            return *this;
        }
        inline constexpr v3f& operator+=(v3f const& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this;
        }
        inline constexpr v3f& operator-=(float scalar) {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            return *this;
        }
        inline constexpr v3f& operator-=(v3f const& v) {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            return *this;
        }
        // Increment and decrement operators
        inline constexpr v3f& operator++() {
            ++this->x;
            ++this->y;
            ++this->z;
            return *this;
        }
        inline constexpr v3f& operator--() {
            --this->x;
            --this->y;
            --this->z;
            return *this;
        }
    }v3f;

    typedef struct v4f{
        union{float x, r;};
        union{float y, g;};
        union{float z, b;};
        union{float w, a;};
        // Component Access
        typedef int length_t;
        static constexpr length_t length(){return 4;}
        constexpr float & operator[](length_t i) {
            assert(i >= 0 && i < this->length());
            switch(i)
            {
                default:
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                case 3:
                    return w;
            }
        }
        constexpr float const& operator[](length_t i) const {
            assert(i >= 0 && i < this->length());
            switch(i)
            {
                default:
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                case 3:
                    return w;
            }
        }
        // Implicit basic constructors
        inline constexpr v4f(v4f const& v) : x(v.x), y(v.y), z(v.z), w(v.w){}
        // Explicit basic constructors
        inline constexpr explicit v4f(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar){}
        inline constexpr v4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
        // Unary arithmetic operators
        inline constexpr v4f& operator=(v4f const& v) = default;
        inline constexpr v4f& operator+=(float scalar) {
            this->x += scalar;
            this->y += scalar;
            this->z += scalar;
            this->w += scalar;
            return *this;
        }
        inline constexpr v4f& operator+=(v4f const& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            this->w += v.w;
            return *this;
        }
        inline constexpr v4f& operator-=(float scalar) {
            this->x -= scalar;
            this->y -= scalar;
            this->z -= scalar;
            this->w -= scalar;
            return *this;
        }
        inline constexpr v4f& operator-=(v4f const& v) {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            this->w -= v.w;
            return *this;
        }
        // Increment and decrement operators
        inline constexpr v4f& operator++() {
            ++this->x;
            ++this->y;
            ++this->z;
            ++this->w;
            return *this;
        }
        inline constexpr v4f& operator--() {
            --this->x;
            --this->y;
            --this->z;
            --this->w;
            return *this;
        }
    }v4f;

    typedef struct mat3f{
        typedef v3f col_type;
        typedef v3f row_type;
    private:
        v3f values[3];
    public:
        // Component Access
        typedef int length_t;
        static constexpr length_t length(){return 3;}
        col_type & operator[](length_t i) {
            assert(i < this->length());
            return this->values[i];
        }
        constexpr col_type const& operator[](length_t i) const {
            assert(i < this->length());
            return this->values[i];
        }
        // Implicit basic constructors
        inline constexpr mat3f()
                : values{
                v3f(1.0, .0, .0),
                v3f(.0, 1.0, .0),
                v3f(.0, .0, 1.0)
        } {}
        inline constexpr mat3f(mat3f const& m)
                : values{
                v3f(m.values[0]),
                v3f(m.values[1]),
                v3f(m.values[2])
        } {}
        // Explicit basic constructors
        inline constexpr explicit mat3f(float s)
                : values{
                v3f(s, .0, .0),
                v3f(.0, s, .0),
                v3f(.0, .0, s)
        } {}
        inline constexpr mat3f(v3f const& a, v3f const& b, v3f const& c)
                : values{a, b, c} {}
        // Unary arithmetic operators
        inline constexpr mat3f& operator=(mat3f const& v) = default;
        inline constexpr mat3f& operator+=(float scalar)
        {
            this->values[0] += scalar;
            this->values[1] += scalar;
            this->values[2] += scalar;
            return *this;
        }
        inline constexpr mat3f& operator+=(mat3f const& m)
        {
            this->values[0] += m[0];
            this->values[1] += m[1];
            this->values[2] += m[2];
            return *this;
        }
        inline constexpr mat3f& operator-=(float scalar)
        {
            this->values[0] -= scalar;
            this->values[1] -= scalar;
            this->values[2] -= scalar;
            return *this;
        }
        inline constexpr mat3f& operator-=(mat3f const& m)
        {
            this->values[0] -= m[0];
            this->values[1] -= m[1];
            this->values[2] -= m[2];
            return *this;
        }
    }mat3f;

    typedef struct mat4f{
        typedef v4f col_type;
        typedef v4f row_type;
    private:
        v4f values[4];
    public:
        // Component Access
        typedef int length_t;
        static constexpr length_t length(){return 4;}
        col_type & operator[](length_t i) {
            assert(i < this->length());
            return this->values[i];
        }
        constexpr col_type const& operator[](length_t i) const {
            assert(i < this->length());
            return this->values[i];
        }
        // Implicit basic constructors
        inline constexpr mat4f()
                : values{
                v4f(1.0, .0, .0, .0),
                v4f(.0, 1.0, .0, .0),
                v4f(.0, .0, 1.0, .0),
                v4f(.0, .0, .0, 1.0)
        } {}
        inline constexpr mat4f(mat4f const& m)
                : values{
                v4f(m.values[0]),
                v4f(m.values[1]),
                v4f(m.values[2]),
                v4f(m.values[3])
        } {}
        // Explicit basic constructors
        inline constexpr explicit mat4f(float s)
                : values{
                v4f(s, .0, .0, .0),
                v4f(.0, s, .0, .0),
                v4f(.0, .0, s, .0),
                v4f(.0, .0, .0, s)
        } {}
        inline constexpr mat4f(v4f const& a, v4f const& b, v4f const& c, v4f const& d)
        : values{a, b, c, d} {}
        // Unary arithmetic operators
        inline constexpr mat4f& operator=(mat4f const& v) = default;
        inline constexpr mat4f& operator+=(float scalar)
        {
            this->values[0] += scalar;
            this->values[1] += scalar;
            this->values[2] += scalar;
            this->values[3] += scalar;
            return *this;
        }
        inline constexpr mat4f& operator+=(mat4f const& m)
        {
            this->values[0] += m[0];
            this->values[1] += m[1];
            this->values[2] += m[2];
            this->values[3] += m[3];
            return *this;
        }
        inline constexpr mat4f& operator-=(float scalar)
        {
            this->values[0] -= scalar;
            this->values[1] -= scalar;
            this->values[2] -= scalar;
            this->values[3] -= scalar;
            return *this;
        }
        inline constexpr mat4f& operator-=(mat4f const& m)
        {
            this->values[0] -= m[0];
            this->values[1] -= m[1];
            this->values[2] -= m[2];
            this->values[3] -= m[3];
            return *this;
        }
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
