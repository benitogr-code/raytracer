#pragma once

#include "entity.h"

class SphereEntity : public IEntity {
public:
    SphereEntity(const Sphere& sphere, IMaterialPtr material)
        : _sphere(sphere)
        , _material(material)
        , _velocity(0.0f, 0.0f, 0.0f) {}

    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual void setVelocity(const Vec3& velocity) override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;

private:
    Vec3 getPosition(float time) const {
        return _sphere.center + (_velocity * time);
    }

private:
    Sphere _sphere;
    IMaterialPtr _material;
    Vec3 _velocity;
};
