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
