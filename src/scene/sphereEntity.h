#pragma once

#include "entity.h"

class SphereEntity : public IEntity {
public:
    SphereEntity(const Sphere& sphere, IMaterialPtr material)
        : _sphere(sphere)
        , _material(material) {}

    virtual void setMaterial(IMaterialPtr material) override;
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;

private:
    Sphere _sphere;
    IMaterialPtr _material;
};
