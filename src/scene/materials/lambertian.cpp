#include "lambertian.h"

#include "../../common/hittable.h"

bool Lambertian::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const Vec3 scatteredDir = hit.normal + Vec3::randomUnit();
    scattered = Ray(hit.point, Vec3::normalize(scatteredDir), ray.time);
    attenuation = _albedo->value(hit.u, hit.v, hit.point);

    return true;
}
