#pragma once

#include "../../common/material.h"
#include "../../common/texture.h"
#include "../textures/solidColor.h"

class Lambertian : public IMaterial {
public:
    Lambertian(const Color& c)
    : _albedo(std::make_shared<SolidColor>(c)) {}

    Lambertian(ITexturePtr texture)
    : _albedo(texture) {}

    // IMaterial
    virtual Color emit(float u, float v, const Vec3& pos) const override;
    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

public:
    ITexturePtr _albedo;
};
