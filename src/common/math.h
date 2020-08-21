#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>

// Misc /////

namespace Math {
    const float MaxFloat = std::numeric_limits<float>::infinity();
    const float Pi = 3.1415926535897932385f;

    template<typename T>
    inline bool inRange(const T& value, const T& min, const T& max) {
        return (value >= min) && (value <= max);
    }

    inline float randf() {
        return (float)rand() / (float)(RAND_MAX + 1.0f);
    }

    inline float randf(float min, float max) {
        return min + (max-min)*randf();
    }

    inline float clampf(float value, float min, float max) {
        return std::max(min, std::min(value, max));
    }
}

// Vec3 ///////////

struct Vec3 {
    Vec3() : _v{0.0f, 0.0f, 0.0f} {}
    Vec3(float x, float y, float z) : _v{x, y, z} {}

    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }
    Vec3& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }
    Vec3& operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }
    Vec3& operator/=(float f) {
        x /= f;
        y /= f;
        z /= f;

        return *this;
    }

    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }

    Vec3 operator/(float f) const {
        return Vec3(x / f, y / f, z / f);
    }

    float length() const {
        return std::sqrtf(lengthSqr());
    }
    float lengthSqr() const {
        return (x*x) + (y*y) + (z*z);
    }

    static Vec3 normalize(const Vec3& v) {
        return v / v.length();
    }

    static float dot(const Vec3& a, const Vec3& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    static Vec3 cross(const Vec3& a, const Vec3& b) {
        const float x = a.y * b.z - a.z * b.y;
        const float y = a.z * b.x - a.x * b.z;
        const float z = a.x * b.y - a.y * b.x;

        return Vec3(x, y, z);
    }

    static Vec3 random() {
        return Vec3(Math::randf(), Math::randf(), Math::randf());
    }

    static Vec3 random(float min, float max) {
        return Vec3(
            Math::randf(min, max),
            Math::randf(min, max),
            Math::randf(min, max)
        );
    }

    union {
        struct { float x, y, z; };
        float _v[3];
    };
};

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(const Vec3& v, float f) {
    return Vec3(v.x * f, v.y * f, v.z * f);
}

inline Vec3 operator*(float f, const Vec3 &v) {
    return Vec3(f*v.x, f*v.y, f*v.z);
}
