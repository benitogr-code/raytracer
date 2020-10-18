#pragma once

#include "../../common/perlin.h"
#include "../../common/texture.h"

class Noise : public ITexture {
public:
    Noise()
    : _scale(1.0f) {}

    Noise(float scale)
    : _scale(scale) {}

    // ITexture
    virtual Color value(float u, float v, const Vec3& p) const override {
        return Color(1.0f, 1.0f, 1.0f) * _perlin.noise(p * _scale);
    }

private:
    Perlin _perlin;
    float _scale;
};
