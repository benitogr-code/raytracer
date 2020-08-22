#include "dielectric.h"

#include "../../common/geometry.h"
#include "../../common/hitInfo.h"

#include <iostream>

bool Dielectric::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const float etaiOverEtat = hit.frontFace ? (1.0f / _refractionIndex) : _refractionIndex;

    const float cosTheta = Math::min(Vec3::dot(-ray.direction, hit.normal), 1.0f);
    const float sinTheta = sqrt(1.0f - cosTheta*cosTheta);

    const bool shouldReflect = (etaiOverEtat * sinTheta) > 1.0f;

    if (shouldReflect || (Math::randf() < Math::schlick(cosTheta, etaiOverEtat))) {
        const Vec3 reflected = Math::reflect(ray.direction, hit.normal);
        scattered = Ray(hit.point, Vec3::normalize(reflected));
    }
    else {
        const Vec3 refracted = Math::refract(ray.direction, hit.normal, etaiOverEtat);
        scattered = Ray(hit.point, Vec3::normalize(refracted));
    }

    attenuation = Color(1.0f, 1.0f, 1.0f);

    return true;
}
