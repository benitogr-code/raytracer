#include "entityRect.h"

bool EntityRect::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    const Vec3 normal = _rect.normal();
    const Vec3 diff = _rect.p0 - ray.origin;

    const float t = Vec3::dot(diff, normal) / Vec3::dot(ray.direction, normal);

    if (!Math::inRange(t, tMin, tMax))
        return false;

    const auto hitPoint = ray.pointAt(t);
    const auto inTriangle1 = isPointInTriangle(hitPoint, _rect.p0, _rect.p1, _rect.p2);
    const auto inTriangle2 = isPointInTriangle(hitPoint, _rect.p0, _rect.p2, _rect.p3);

    if (!inTriangle1 && !inTriangle2)
        return false;

    const auto frontFace = HitInfo::isFrontFace(ray, normal);

    outHit.point = hitPoint;
    outHit.t = t;
    outHit.normal = frontFace ? normal : -normal;
    outHit.frontFace = frontFace;
    outHit.material = material();
    outHit.u = 0.5f; // TODO
    outHit.v = 0.5f;

    return true;
}

bool EntityRect::getAABB(float t0, float t1, AABB& bbox) const {
    const Vec3 epsilon(0.0001f, 0.0001f, 0.0001f);

    Vec3 min = _rect.p0;
    Vec3 max = _rect.p0;

    const Vec3 points[3] = { _rect.p1, _rect.p2, _rect.p3 };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; j++) {
            min._v[j] = Math::min(min._v[j], points[i]._v[j]);
            max._v[j] = Math::max(max._v[j], points[i]._v[j]);
        }
    }

    bbox = AABB(min-epsilon, max+epsilon);

    return true;
}

/*static*/ bool EntityRect::isPointInTriangle(const Vec3& p, const Vec3& v0, const Vec3& v1, const Vec3& v2) {
    return sameSide(p, v0, v1, v2) && sameSide(p, v1, v0, v2) && sameSide(p, v2, v0, v1);
}

/*static*/ bool EntityRect::sameSide(const Vec3 &p1, const Vec3 &p2, const Vec3 &a, const Vec3 &b) {
    auto v1 = Vec3::cross((b - a), (p1 - a));
    auto v2 = Vec3::cross((b - a), (p2 - a));

    return Vec3::dot(v1, v2) >= 0.0f;
}
