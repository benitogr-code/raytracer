#pragma once

#include "../../common/color.h"
#include "../../common/material.h"

class Dielectric : public IMaterial {
public:
    Dielectric(float refractionIndex)
    : _refractionIndex(refractionIndex) {}

    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

public:
    float _refractionIndex;
};
