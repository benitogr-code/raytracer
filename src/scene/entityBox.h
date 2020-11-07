#pragma once

#include <vector>
#include "entity.h"

class EntityBox : public Entity {
public:
    EntityBox(const Vec3& p0, const Vec3& p1, IMaterialPtr material);

    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    Vec3 _min;
    Vec3 _max;
    std::vector<EntityPtr> _sides;
};
