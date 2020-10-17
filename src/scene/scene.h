#pragma once

#include <vector>

#include "../common/hittable.h"
#include "bvh.h"

class Scene {
private:
    typedef std::vector<IHittablePtr> Entities;

public:
    void addEntity(IHittablePtr entity) {
        _entities.push_back(entity);
    }

    void buildBvh(float t0, float t1);
    bool rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const;

private:
    Entities _entities;
    BvhTreePtr _bvh;
};
