#pragma once

#include "entity.h"

class Rect : public Entity {
public:
    Rect(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3, IMaterialPtr material)
    : Entity(material) {
        _points[0] = p0;
        _points[1] = p1;
        _points[2] = p2;
        _points[3] = p3;

        computeRect();
    }

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override {
        bbox = _bbox;
        return true;
    }
    //~IHittable

protected:
    void computeRect();

    // Entity
    virtual void onWorldTMChanged(const Mat4x4& m) override {
        computeRect();
    }

private:
    Vec3 _points[4];
    Vec3 _worldPoints[4];
    Vec3 _worldNormal;
    AABB _bbox;
};
