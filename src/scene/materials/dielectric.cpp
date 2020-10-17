#include "dielectric.h"

#include "../../common/hittable.h"

bool Dielectric::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const float etaiOverEtat = hit.frontFace ? (1.0f / _refractionIndex) : _refractionIndex;

    const float cosTheta = Math::min(Vec3::dot(-ray.direction, hit.normal), 1.0f);
    const float sinTheta = sqrt(1.0f - cosTheta*cosTheta);

    const bool shouldReflect = (etaiOverEtat * sinTheta) > 1.0f;

    if (shouldReflect || (Math::randf() < Math::schlick(cosTheta, etaiOverEtat))) {
        const Vec3 reflected = VectorUtils::reflect(ray.direction, hit.normal);
        scattered = Ray(hit.point, Vec3::normalize(reflected), ray.time);
    }
    else {
        const Vec3 refracted = VectorUtils::refract(ray.direction, hit.normal, etaiOverEtat);
        scattered = Ray(hit.point, Vec3::normalize(refracted), ray.time);
    }

    attenuation = Color(1.0f, 1.0f, 1.0f);

    return true;
}
