#pragma once

#include <vector>

#include "../common/hittable.h"

class Scene {
private:
    typedef std::vector<IHittablePtr> Entities;

public:
    void addEntity(IHittablePtr entity) {
        _entities.push_back(entity);
    }

    bool rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const;
    bool getAABB(float t0, float t1, AABB& bbox) const;

private:
    Entities _entities;
};
