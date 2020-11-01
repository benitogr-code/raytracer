#pragma once

#include "entity.h"

struct Rect {
    Rect() {}
    Rect(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2, const Vec3& _p3)
        : p0(_p0)
        , p1(_p1)
        , p2(_p2)
        , p3(_p3) {}

    Vec3 normal() const {
        auto u = Vec3::normalize(p1-p0);
        auto v = Vec3::normalize(p2-p0);
        return Vec3::normalize(Vec3::cross(u, v));
    }

    Vec3  p0, p1, p2, p3;
};

class EntityRect : public Entity {
public:
    EntityRect(const Rect& rect, IMaterialPtr material)
    : Entity(material) {
        _rect = rect;
    }

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    static bool isPointInTriangle(const Vec3& p, const Vec3& v0, const Vec3& v1, const Vec3& v2);
    static bool sameSide(const Vec3 &p1, const Vec3 &p2, const Vec3 &a, const Vec3 &b);

private:
    Rect _rect;
};
