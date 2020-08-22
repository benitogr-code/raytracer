#include "sphereEntity.h"

void SphereEntity::setMaterial(IMaterialPtr material) {
    _material = material;
}

bool SphereEntity::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    // Resolve quadratic equation terms
    const Vec3 sphereToRayOrigin = ray.origin - _sphere.center;
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
        const auto normal = (point - _sphere.center) / _sphere.radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = ray.pointAt(t1);
        outHit.t = t1;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = _material;

        return true;
    }

    const float t2 = (-b + sqrtD) / (2.0f*a);
    if (Math::inRange(t2, tMin, tMax)) {
        const auto point = ray.pointAt(t2);
        const auto normal = (point - _sphere.center) / _sphere.radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = ray.pointAt(t1);
        outHit.t = t2;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = _material;

        return true;
    }

    return false;
}
