#include "box.h"
#include "rect.h"

Box::Box(const Vec3& p0, const Vec3& p1, IMaterialPtr material)
: Entity(material) {
    _min = p0;
    _max = p1;

    _sides.push_back(std::make_shared<Rect>(
        Vec3(p0.x, p0.y, p0.z),
        Vec3(p1.x, p0.y, p0.z),
        Vec3(p1.x, p1.y, p0.z),
        Vec3(p0.x, p1.y, p0.z),
        material
    ));
    _sides.push_back(std::make_shared<Rect>(
        Vec3(p0.x, p0.y, p1.z),
        Vec3(p1.x, p0.y, p1.z),
        Vec3(p1.x, p1.y, p1.z),
        Vec3(p0.x, p1.y, p1.z),
        material
    ));
    _sides.push_back(std::make_shared<Rect>(
        Vec3(p0.x, p0.y, p0.z),
        Vec3(p1.x, p0.y, p0.z),
        Vec3(p1.x, p0.y, p1.z),
        Vec3(p0.x, p0.y, p1.z),
        material
    ));
    _sides.push_back(std::make_shared<Rect>(
        Vec3(p0.x, p1.y, p0.z),
        Vec3(p1.x, p1.y, p0.z),
        Vec3(p1.x, p1.y, p1.z),
        Vec3(p0.x, p1.y, p1.z),
        material
    ));
    _sides.push_back(std::make_shared<Rect>(
        Vec3(p0.x, p0.y, p0.z),
        Vec3(p0.x, p0.y, p1.z),
        Vec3(p0.x, p1.y, p1.z),
        Vec3(p0.x, p1.y, p0.z),
        material
    ));
    _sides.push_back(std::make_shared<Rect>(
        Vec3(p1.x, p0.y, p0.z),
        Vec3(p1.x, p0.y, p1.z),
        Vec3(p1.x, p1.y, p1.z),
        Vec3(p1.x, p1.y, p0.z),
        material
    ));
}

bool Box::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
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

bool Box::getAABB(float t0, float t1, AABB& bbox) const {
    const Vec3 points[8] = {
        (worldTM() * Vec4(_min.x, _min.y, _min.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_max.x, _min.y, _min.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_max.x, _max.y, _min.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_min.x, _max.y, _min.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_min.x, _min.y, _max.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_max.x, _min.y, _max.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_max.x, _max.y, _max.z, 1.0f)).toVec3(),
        (worldTM() * Vec4(_min.x, _max.y, _max.z, 1.0f)).toVec3(),
    };

    Vec3 min = points[0];
    Vec3 max = points[0];

    for (int i = 1; i < 8; ++i) {
        for (int j = 0; j < 3; j++) {
            min._v[j] = Math::min(min._v[j], points[i]._v[j]);
            max._v[j] = Math::max(max._v[j], points[i]._v[j]);
        }
    }

    bbox = AABB(min, max);

    return true;
}
