#pragma once

#include "../../common/material.h"
#include "../textures/solidColor.h"

class DiffuseLight : public IMaterial  {
public:
    DiffuseLight(ITexturePtr texture)
    : _emitColor(texture) {}

    DiffuseLight(const Color& c)
    : _emitColor(std::make_shared<SolidColor>(c)) {}

    // IMaterial
    virtual Color emit(float u, float v, const Vec3& pos) const override {
        return _emitColor->value(u, v, pos);
    }
    virtual bool scatter(const Ray& ray, const HitInfo& hit, Color& attenuation, Ray& scattered) const override {
        return false;
    }

private:
    ITexturePtr _emitColor;
};
