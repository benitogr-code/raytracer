#include "rect.h"

static bool sameSide(const Vec3 &p1, const Vec3 &p2, const Vec3 &a, const Vec3 &b) {
    auto v1 = Vec3::cross((b - a), (p1 - a));
    auto v2 = Vec3::cross((b - a), (p2 - a));

    return Vec3::dot(v1, v2) >= 0.0f;
}

static bool isPointInTriangle(const Vec3& p, const Vec3& v0, const Vec3& v1, const Vec3& v2) {
    return sameSide(p, v0, v1, v2) && sameSide(p, v1, v0, v2) && sameSide(p, v2, v0, v1);
}

bool Rect::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    const Vec3 diff = _worldPoints[0] - ray.origin;

    const float t = Vec3::dot(diff, _worldNormal) / Vec3::dot(ray.direction, _worldNormal);

    if (!Math::inRange(t, tMin, tMax))
        return false;

    const auto hitPoint = ray.pointAt(t);
    const auto inTriangle1 = isPointInTriangle(hitPoint, _worldPoints[0], _worldPoints[1], _worldPoints[2]);
    const auto inTriangle2 = isPointInTriangle(hitPoint, _worldPoints[0], _worldPoints[2], _worldPoints[3]);

    if (!inTriangle1 && !inTriangle2)
        return false;

    const auto frontFace = HitInfo::isFrontFace(ray, _worldNormal);

    outHit.point = hitPoint;
    outHit.t = t;
    outHit.normal = frontFace ? _worldNormal : -_worldNormal;
    outHit.frontFace = frontFace;
    outHit.material = material();
    outHit.u = 0.5f; // TODO
    outHit.v = 0.5f;

    return true;
}

bool Rect::getAABB(float t0, float t1, AABB& bbox) const {
    const Vec3 epsilon(0.0001f, 0.0001f, 0.0001f);

    Vec3 min = _worldPoints[0];
    Vec3 max = _worldPoints[0];

    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 3; j++) {
            min._v[j] = Math::min(min._v[j], _worldPoints[i]._v[j]);
            max._v[j] = Math::max(max._v[j], _worldPoints[i]._v[j]);
        }
    }

    bbox = AABB(min-epsilon, max+epsilon);

    return true;
}
