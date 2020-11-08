#include "box.h"
#include "rect.h"

Box::Box(const Vec3& p0, const Vec3& p1, IMaterialPtr material)
: Entity(material) {
    _sourcePoints[0] = p0;
    _sourcePoints[1] = p1;

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

    computeBBox();
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

void Box::computeBBox() {
    const auto p0 = _sourcePoints[0];
    const auto p1 = _sourcePoints[1];

    const Vec3 points[8] = {
        (_worldTM * Vec4(p0.x, p0.y, p0.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p1.x, p0.y, p0.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p1.x, p1.y, p0.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p0.x, p1.y, p0.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p0.x, p0.y, p1.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p1.x, p0.y, p1.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p1.x, p1.y, p1.z, 1.0f)).toVec3(),
        (_worldTM * Vec4(p0.x, p1.y, p1.z, 1.0f)).toVec3(),
    };

    Vec3 min = points[0];
    Vec3 max = points[0];

    for (int i = 1; i < 8; ++i) {
        for (int j = 0; j < 3; j++) {
            min._v[j] = Math::min(min._v[j], points[i]._v[j]);
            max._v[j] = Math::max(max._v[j], points[i]._v[j]);
        }
    }

    _bbox = AABB(min, max);
}
