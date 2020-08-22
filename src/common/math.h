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
        return (value > min) && (value < max);
    }

    template<typename T>
    inline float min(const T& a, const T& b) {
        return std::min<T>(a, b);
    }

    template<typename T>
    inline float max(const T& a, const T& b) {
        return std::max<T>(a, b);
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

    static Vec3 randomUnit() {
        const float a = Math::randf(0.0f, 2.0f*Math::Pi);
        const float z = Math::randf(-1.0f, 1.0f);
        const float r = sqrt(1.0f - z*z);

        return Vec3(r*cos(a), r*sin(a), z);
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

namespace Math {
    inline Vec3 reflect(const Vec3& v, const Vec3& n) {
        return v - 2.0f*Vec3::dot(v,n)*n;
    }

    // Refraction: https://en.wikipedia.org/wiki/Snell's_law
    inline Vec3 refract(const Vec3& v, const Vec3& n, float etaiOverEtat) {
        const float cosTheta = Vec3::dot(-v, n);
        const Vec3 rPerp = etaiOverEtat * (v + (cosTheta*n));
        const Vec3 rParallel = -sqrt(fabs(1.0f - rPerp.lengthSqr())) * n;

        return rPerp + rParallel;
    }

    inline float schlick(float cosine, float refractionIndex) {
        float r0 = (1-refractionIndex) / (1+refractionIndex);
        r0 *= r0;

        return r0 + (1.0f-r0)*pow((1.0f - cosine),5);
    }
}
