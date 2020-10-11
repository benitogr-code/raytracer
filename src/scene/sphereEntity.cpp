#include "sphereEntity.h"

bool SphereEntity::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    // Resolve quadratic equation terms
    const Vec3 spherePos = getPosition(ray.time);
    const Vec3 sphereToRayOrigin = ray.origin - spherePos;
    const float a = Vec3::dot(ray.direction, ray.direction);
    const float b = 2.0f * Vec3::dot(ray.direction, sphereToRayOrigin);
    const float c = Vec3::dot(sphereToRayOrigin, sphereToRayOrigin) - (_sphere.radius * _sphere.radius);

    // Calculate discriminant term
    const float d = (b * b) - (4.0f * a * c);

    if (d < 0.0f)
        return false;

    const float sqrtD = sqrt(d);

    const float t1 = (-b - sqrtD) / (2.0f*a);
    if (Math::inRange(t1, tMin, tMax)) {
        const auto point = ray.pointAt(t1);
        const auto normal = (point - spherePos) / _sphere.radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = point;
        outHit.t = t1;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = _material;

        return true;
    }

    const float t2 = (-b + sqrtD) / (2.0f*a);
    if (Math::inRange(t2, tMin, tMax)) {
        const auto point = ray.pointAt(t2);
        const auto normal = (point - spherePos) / _sphere.radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = point;
        outHit.t = t2;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = _material;

        return true;
    }

    return false;
}

void SphereEntity::setVelocity(const Vec3& velocity) {
    _velocity = velocity;
}
