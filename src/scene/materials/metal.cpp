#include "metal.h"

#include "../../common/geometry.h"
#include "../../common/hitInfo.h"

bool Metal::scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const {
    const Vec3 reflect = VectorUtils::reflect(ray.direction, hit.normal);
    scattered = Ray(hit.point, Vec3::normalize(reflect + _fuzzy*Vec3::randomUnit()), ray.time);
    attenuation = _albedo;

    return (Vec3::dot(scattered.direction, hit.normal) > 0);
}
