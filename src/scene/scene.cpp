#include "scene.h"

void Scene::buildBvh(float t0, float t1) {
    _bvh = std::make_shared<BvhTree>(_entities, t0, t1);
}

bool Scene::rayTrace(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    return _bvh->hit(ray, tMin, tMax, outHit);
}
