#pragma once

#include <vector>
#include "entity.h"

class Box : public Entity {
public:
    Box(const Vec3& p0, const Vec3& p1, IMaterialPtr material);

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override {
        bbox = _bbox;
        return true;
    }
    //~IHittable

protected:
    void computeBBox();

    // Entity
    virtual void onWorldTMChanged(const Mat4x4& m) override {
        for (const auto& side : _sides) {
            side->setWorldTM(m);
        }
        computeBBox();
    }

private:
    Vec3 _sourcePoints[2];
    AABB _bbox;
    std::vector<EntityPtr> _sides;
};
