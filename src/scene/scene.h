#pragma once

#include <vector>

#include "entity.h"

class Scene {
private:
    typedef std::vector<IEntityPtr> Entities;

public:
    void addEntity(IEntityPtr entity) {
        _entities.push_back(entity);
    }

    bool rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const;
    bool getAABB(float t0, float t1, AABB& bbox) const;

private:
    Entities _entities;
};
