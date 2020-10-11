#include "scene.h"

bool Scene::rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    bool registeredHit = false;
    float closest = tMax;

    for (const auto& entity : _entities) {
        HitInfo hit;
        if (!entity->hit(ray, tMin, closest, hit))
            continue;

        outHit = hit;
        registeredHit = true;
        closest = hit.t;
    }

    return registeredHit;
}

bool Scene::getAABB(float t0, float t1, AABB& bbox) const {
    if (_entities.empty()) {
        return false;
    }

    bool firstBox = true;
    AABB temp;

    for (const auto& entity : _entities) {
        if (!entity->getAABB(t0, t1, temp)) {
            return false;
        }

        bbox = firstBox ? temp: AABB::surroundingBox(bbox, temp);
        firstBox = false;
    }

    return true;
}
