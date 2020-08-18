#pragma once

#include "math.h"

struct Ray {
    Ray() {}
    Ray(const Vec3& _origin, const Vec3& _direction)
        : origin(_origin)
        , direction(_direction) {}

    Vec3 pointAt(float t) const {
        return origin + (direction * t);
    }

    Vec3 origin;
    Vec3 direction;
};

struct Sphere {
    Sphere() {}
    Sphere(const Vec3& _center, float _radius)
        : center(_center)
        , radius(_radius) {}

    Vec3  center;
    float radius;
};
