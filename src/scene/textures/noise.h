#pragma once

#include "../../common/perlin.h"
#include "../../common/texture.h"

class NoiseTexture : public ITexture {
public:
    NoiseTexture()
    : _scale(1.0f) {}

    NoiseTexture(float scale)
    : _scale(scale) {}

    // ITexture
    virtual Color value(float u, float v, const Vec3& pos) const override {
        return Color(1.0f, 1.0f, 1.0f) * 0.5f * (1.0f + sinf(_scale*pos.z + 10.0f*_perlin.turbulence(pos)));
    }

private:
    Perlin _perlin;
    float _scale;
};
