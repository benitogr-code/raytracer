#pragma once

#include "entity.h"

class EntitySphere : public Entity<Sphere> {
public:
    EntitySphere(const Sphere& sphere, IMaterialPtr material)
        : Entity(sphere, material){}

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    Vec3 getPosition(float time) const;
    void getUVCoords(const Vec3& p, float& u, float& v) const;
};
