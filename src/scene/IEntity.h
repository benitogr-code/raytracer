#pragma once

#include <memory>

#include "../common/math.h"
#include "../common/geometry.h"

struct HitInfo {
    HitInfo() {};

    static bool isFrontFace(const Ray& ray, const Vec3& normal) {
        return Vec3::dot(ray.direction, normal) < 0.0f;
    }

    Vec3 point;
    Vec3 normal;
    float t;
    bool frontFace;
};

struct IEntity {
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const = 0;
};

typedef std::shared_ptr<IEntity> IEntityPtr;
