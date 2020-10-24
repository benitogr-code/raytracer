#pragma once

#include "../../common/material.h"
#include "../../common/texture.h"
#include "../textures/solidColor.h"

class Metal : public IMaterial {
public:
    Metal(const Color& albedo, float fuzzy)
    : _albedo(std::make_shared<SolidColor>(albedo))
    , _fuzzy(fuzzy) {}

    Metal(ITexturePtr texture, float fuzzy)
    : _albedo(texture)
    , _fuzzy(fuzzy) {}

    // IMaterial
    virtual Color emit(float u, float v, const Vec3& pos) const override;
    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

private:
    ITexturePtr _albedo;
    float _fuzzy;
};
