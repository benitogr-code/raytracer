#pragma once

#include <memory>

#include "aabb.h"
#include "material.h"
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

struct HitInfo {
    HitInfo() {};

    static bool isFrontFace(const Ray& ray, const Vec3& normal) {
        return Vec3::dot(ray.direction, normal) < 0.0f;
    }

    Vec3 point;     // Surface hit position
    Vec3 normal;    // Surface hit normal
    IMaterialPtr material;
    float u;        // [u,v] coordinates (for textures)
    float v;
    float t;        // 't' value at ray hit
    bool frontFace; // Front face hit flag
};

struct IHittable {
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const = 0;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const = 0;
};

typedef std::shared_ptr<IHittable> IHittablePtr;
