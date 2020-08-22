#pragma once

#include <memory>

struct HitInfo;
struct Ray;
struct Color;

struct IMaterial {
public:
    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const = 0;
};

typedef std::shared_ptr<IMaterial> IMaterialPtr;
