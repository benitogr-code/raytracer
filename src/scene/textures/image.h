#pragma once

#include <vector>

#include "../../common/texture.h"

class ImageTexture : public ITexture {
    enum {
        BytesPerPixel = 3
    };

public:
    ImageTexture();
    ImageTexture(const char* szFilePath);

    // ITexture
    virtual Color value(float u, float v, const Vec3& p) const override;

private:
    std::vector<unsigned char> _data;
    int _width;
    int _height;
};
