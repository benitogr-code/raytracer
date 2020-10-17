#pragma once

#include "aabb.h"
#include "geometry.h"
#include "material.h"

struct HitInfo {
    HitInfo() {};

    static bool isFrontFace(const Ray& ray, const Vec3& normal) {
        return Vec3::dot(ray.direction, normal) < 0.0f;
    }

    Vec3 point;
    Vec3 normal;
    IMaterialPtr material;
    float t;
    bool frontFace;
};

struct IHittable {
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const = 0;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const = 0;
};
