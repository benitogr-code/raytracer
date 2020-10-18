#pragma once

#include <vector>

#include "../common/hittable.h"
#include "bvh.h"

class Scene {
public:
    void build(std::vector<IHittablePtr> entities, float t0, float t1) {
        _bvh = std::make_shared<BvhTree>(entities, t0, t1);
    }

    bool rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
        return _bvh->hit(ray, tMin, tMax, outHit);
    }

private:
    BvhTreePtr _bvh;
};
