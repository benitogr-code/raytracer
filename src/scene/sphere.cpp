#include "sphere.h"

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    // Resolve quadratic equation terms
    const Vec3 spherePos = getWorldPos(ray.time);
    const Vec3 sphereToRayOrigin = ray.origin - spherePos;
    const float a = Vec3::dot(ray.direction, ray.direction);
    const float b = 2.0f * Vec3::dot(ray.direction, sphereToRayOrigin);
    const float c = Vec3::dot(sphereToRayOrigin, sphereToRayOrigin) - (_radius * _radius);

    // Calculate discriminant term
    const float d = (b * b) - (4.0f * a * c);

    if (d < 0.0f)
        return false;

    const float sqrtD = sqrt(d);

    const float t1 = (-b - sqrtD) / (2.0f*a);
    if (Math::inRange(t1, tMin, tMax)) {
        const auto point = ray.pointAt(t1);
        const auto normal = (point - spherePos) / _radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = point;
        outHit.t = t1;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = material();
        getUVCoords(normal, outHit.u, outHit.v);

        return true;
    }

    const float t2 = (-b + sqrtD) / (2.0f*a);
    if (Math::inRange(t2, tMin, tMax)) {
        const auto point = ray.pointAt(t2);
        const auto normal = (point - spherePos) / _radius;
        const auto frontFace = HitInfo::isFrontFace(ray, normal);

        outHit.point = point;
        outHit.t = t2;
        outHit.normal = frontFace ? normal : -normal;
        outHit.frontFace = frontFace;
        outHit.material = material();
        getUVCoords(normal, outHit.u, outHit.v);

        return true;
    }

    return false;
}

bool Sphere::getAABB(float t0, float t1, AABB& bbox) const {
    const Vec3 radius(_radius, _radius, _radius);
    const Vec3 p0 = getWorldPos(t0);
    const Vec3 p1 = getWorldPos(t1);

    const AABB box0(p0-radius, p0+radius);
    const AABB box1(p1-radius, p1+radius);
    bbox = AABB::surroundingBox(box0, box1);

    return true;
}

Vec3 Sphere::getWorldPos(float time) const {
    auto pos = _worldTM.getTranslation();
    return pos + (velocity() * time);
}

void Sphere::getUVCoords(const Vec3& p, float& u, float& v) const {
    // 'p' is a normalized point in the sphere
    const float phi = atan2(p.z, p.x);
    const float theta = asin(p.y);

    u = 1-(phi + Math::Pi) / (2.0f * Math::Pi);
    v = (theta + (Math::Pi / 2.0f)) / Math::Pi;
}
