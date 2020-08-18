#pragma once

#include <cmath>

struct Vec3 {
    Vec3() : _v{0.0f, 0.0f, 0.0f} {}
    Vec3(float x, float y, float z) : _v{x, y, z} {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }
    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    Vec3& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    Vec3 operator*(float f) const {
        return Vec3(x * f, y * f, z * f);
    }
    Vec3& operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }
    Vec3 operator/(float f) const {
        return Vec3(x/f, y/f, z/f);
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

    float dot(const Vec3& v) const {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }
    Vec3 cross(const Vec3& v) const {
        const float _x = y * v.z - z * v.y;
        const float _y = z * v.x - x * v.z;
        const float _z = x * v.y - y * v.x;

        return Vec3(_x, _y, _z);
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

    union {
        struct { float x, y, z; };
        float _v[3];
    };
};
