#pragma once

#include "IEntity.h"

class SphereEntity : public IEntity {
public:
    SphereEntity(const Sphere& sphere)
        : _sphere(sphere) {}

    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;

private:
    Sphere _sphere;
};
