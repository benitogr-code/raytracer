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
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

protected:
    void computeRect() {
        for (int i = 0; i < 4; ++i) {
            _worldPoints[i] = (_worldTM * Vec4(_points[i], 1.0f)).toVec3();
        }
        auto u = Vec3::normalize(_worldPoints[1]-_worldPoints[0]);
        auto v = Vec3::normalize(_worldPoints[2]-_worldPoints[0]);
        _worldNormal = Vec3::normalize(Vec3::cross(u, v));
    }

    // Entity
    virtual void onWorldTMChanged(const Mat4x4& m) override {
        computeRect();
    }

private:
    Vec3 _points[4];
    Vec3 _worldPoints[4];
    Vec3 _worldNormal;
};
