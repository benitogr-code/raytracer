#pragma once

#include "../../common/color.h"
#include "../../common/material.h"

class Metal : public IMaterial {
public:
    Metal(const Color& albedo, float fuzzy)
    : _albedo(albedo)
    , _fuzzy(fuzzy) {}

    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override;

public:
    Color _albedo;
    float _fuzzy;
};
