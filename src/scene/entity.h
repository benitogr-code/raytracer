#pragma once

#include <memory>

#include "../common/geometry.h"
#include "../common/hitInfo.h"
#include "../common/material.h"

struct IEntity {
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const = 0;
    virtual void setVelocity(const Vec3& velocity) = 0;
};

typedef std::shared_ptr<IEntity> IEntityPtr;
