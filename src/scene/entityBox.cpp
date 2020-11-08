#include "entityBox.h"
#include "entityRect.h"

EntityBox::EntityBox(const Vec3& p0, const Vec3& p1, IMaterialPtr material)
: Entity(material) {
    _min = p0;
    _max = p1;

    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p0.x, p0.y, p0.z),
            Vec3(p1.x, p0.y, p0.z),
            Vec3(p1.x, p1.y, p0.z),
            Vec3(p0.x, p1.y, p0.z)
        ),
        material
    ));
    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p0.x, p0.y, p1.z),
            Vec3(p1.x, p0.y, p1.z),
            Vec3(p1.x, p1.y, p1.z),
            Vec3(p0.x, p1.y, p1.z)
        ),
        material
    ));
    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p0.x, p0.y, p0.z),
            Vec3(p1.x, p0.y, p0.z),
            Vec3(p1.x, p0.y, p1.z),
            Vec3(p0.x, p0.y, p1.z)
        ),
        material
    ));
    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p0.x, p1.y, p0.z),
            Vec3(p1.x, p1.y, p0.z),
            Vec3(p1.x, p1.y, p1.z),
            Vec3(p0.x, p1.y, p1.z)
        ),
        material
    ));
    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p0.x, p0.y, p0.z),
            Vec3(p0.x, p0.y, p1.z),
            Vec3(p0.x, p1.y, p1.z),
            Vec3(p0.x, p1.y, p0.z)
        ),
        material
    ));
    _sides.push_back(std::make_shared<EntityRect>(
        Rect(
            Vec3(p1.x, p0.y, p0.z),
            Vec3(p1.x, p0.y, p1.z),
            Vec3(p1.x, p1.y, p1.z),
            Vec3(p1.x, p1.y, p0.z)
        ),
        material
    ));
}

bool EntityBox::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    bool registeredHit = false;
    float closest = tMax;

    for (const auto& side : _sides) {
        HitInfo hit;
        if (!side->hit(ray, tMin, closest, hit))
            continue;

        outHit = hit;
        registeredHit = true;
        closest = hit.t;
    }

    return registeredHit;
}

bool EntityBox::getAABB(float t0, float t1, AABB& bbox) const {
    auto worldMin = worldTM() * Vec4(_min, 1.0f);
    auto worldMax = worldTM() * Vec4(_max, 1.0f);
    bbox = AABB(worldMin.toVec3(), worldMax.toVec3());

    return true;
}