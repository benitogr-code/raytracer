#pragma once

#include "entity.h"

class Sphere : public Entity {
public:
    Sphere(const Vec3& pos, float radius, IMaterialPtr material)
    : Entity(pos, material)
    , _radius(radius) {
    }

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    Vec3 getWorldPos(float time) const;
    void getUVCoords(const Vec3& p, float& u, float& v) const;

private:
    float _radius;
};
