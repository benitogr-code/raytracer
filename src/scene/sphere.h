#pragma once

#include "entity.h"

class Sphere : public Entity {
public:
    Sphere(const Vec3& pos, float radius, IMaterialPtr material)
    : Entity(pos, material)
    , _velocity(0.0f, 0.0f, 0.0f)
    , _radius(radius) {
    }

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

    void setVelocity(const Vec3& v) {
        _velocity = v;
    }

private:
    Vec3 getWorldPos(float time) const;
    void getUVCoords(const Vec3& p, float& u, float& v) const;

private:
    Vec3 _velocity;
    float _radius;
};
