#pragma once

#include "../../common/texture.h"
#include "solidColor.h"

class CheckerTexture : public ITexture {
public:
    CheckerTexture(ITexturePtr t1, ITexturePtr t2)
    : _texture1(t1)
    , _texture2(t2) {}

    CheckerTexture(const Color& c1, const Color& c2)
    : _texture1(std::make_shared<SolidColor>(c1))
    , _texture2(std::make_shared<SolidColor>(c2)) {}

    virtual Color value(float u, float v, const Vec3& p) const override {
        const float value = sin(10*p.x) * sin(10*p.y) *sin(10*p.z);
        const auto& texture = (value < 0.0f) ? _texture1 : _texture2;

        return texture->value(u, v, p);
    }

private:
    ITexturePtr _texture1;
    ITexturePtr _texture2;
};
