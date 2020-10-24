#pragma once

#include "../../common/color.h"
#include "../../common/material.h"

class Dielectric : public IMaterial {
public:
    Dielectric(float refractionIndex)
    : _refractionIndex(refractionIndex) {}

    // IMaterial
    virtual Color emit(float u, float v, const Vec3& pos) const override;
    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

public:
    float _refractionIndex;
};
