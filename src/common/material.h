#pragma once

#include <memory>

struct HitInfo;
struct Ray;
struct Color;
struct Vec3;

struct IMaterial {
    virtual Color emit(float u, float v, const Vec3& pos) const = 0;
    virtual bool  scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const = 0;
};

typedef std::shared_ptr<IMaterial> IMaterialPtr;
