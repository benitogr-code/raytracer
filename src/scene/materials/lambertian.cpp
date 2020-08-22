#include "lambertian.h"

#include "../../common/geometry.h"
#include "../../common/hitInfo.h"

Vec3 randUnitVector() {
    const float a = Math::randf(0.0f, 2.0f*Math::Pi);
    const float z = Math::randf(-1.0f, 1.0f);
    const float r = sqrt(1.0f - z*z);

    return Vec3(r*cos(a), r*sin(a), z);
}

bool Lambertian::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    Vec3 scatteredDir = hit.normal + randUnitVector();
    scattered = Ray(hit.point, Vec3::normalize(scatteredDir));
    attenuation = _albedo;

    return true;
}
