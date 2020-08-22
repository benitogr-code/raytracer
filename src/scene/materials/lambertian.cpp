#include "lambertian.h"

#include "../../common/geometry.h"
#include "../../common/hitInfo.h"

bool Lambertian::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const Vec3 scatteredDir = hit.normal + Vec3::randomUnit();
    scattered = Ray(hit.point, Vec3::normalize(scatteredDir));
    attenuation = _albedo;

    return true;
}
