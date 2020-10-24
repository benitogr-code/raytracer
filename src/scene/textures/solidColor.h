#pragma once

#include "../../common/texture.h"

class SolidColor : public ITexture {
public:
    SolidColor(const Color& c)
    : _color(c) {}

    // ITexture
    virtual Color value(float u, float v, const Vec3& pos) const override {
        return _color;
    }

private:
    Color _color;
};
