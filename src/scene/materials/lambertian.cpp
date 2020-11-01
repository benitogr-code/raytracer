#include "lambertian.h"

#include "../../common/hittable.h"

Color Lambertian::emit(float u, float v, const Vec3& pos) const {
    return Color(0.0f, 0.0f, 0.0f);
}

bool Lambertian::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const Vec3 scatteredDir = hit.normal + Vec3::randomUnit();
    scattered = Ray(hit.point, Vec3::normalize(scatteredDir), ray.time);
    attenuation = _albedo->value(hit.u, hit.v, hit.point);

    return true;
}
