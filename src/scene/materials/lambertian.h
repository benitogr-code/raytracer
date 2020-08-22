#pragma once

#include "../../common/color.h"
#include "../../common/material.h"

class Lambertian : public IMaterial {
public:
    Lambertian(const Color& albedo)
    : _albedo(albedo) {}

    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

public:
    Color _albedo;
};
