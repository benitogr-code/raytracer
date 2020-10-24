#pragma once

#include "entity.h"

struct Sphere {
    Sphere() {}
    Sphere(const Vec3& _center, float _radius)
        : center(_center)
        , radius(_radius) {}

    Vec3  center;
    float radius;
};

class EntitySphere : public Entity {
public:
    EntitySphere(const Sphere& sphere, IMaterialPtr material)
    : Entity(material) {
        _sphere = sphere;
    }

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    Vec3 getPosition(float time) const;
    void getUVCoords(const Vec3& p, float& u, float& v) const;

private:
    Sphere _sphere;
};
