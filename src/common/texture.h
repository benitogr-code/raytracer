#pragma once

#include <memory>

#include "color.h"
#include "vector.h"

struct ITexture {
    virtual Color value(float u, float v, const Vec3& p) const = 0;
};

typedef std::shared_ptr<ITexture> ITexturePtr;
