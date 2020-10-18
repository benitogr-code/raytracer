#pragma once

#include "vector.h"

struct Ray {
    Ray() {}
    Ray(const Vec3& _origin, const Vec3& _direction, float _time)
        : origin(_origin)
        , direction(_direction)
        , time(_time) {}

    Vec3 pointAt(float t) const {
        return origin + (direction * t);
    }

    Vec3 origin;
    Vec3 direction;
    float time;
};

struct Sphere {
    Sphere() {}
    Sphere(const Vec3& _center, float _radius)
        : center(_center)
        , radius(_radius) {}

    Vec3  center;
    float radius;
};
