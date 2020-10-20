#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../common/stb/stb_image.h"

ImageTexture::ImageTexture()
: _width(0)
, _height(0) {}

ImageTexture::ImageTexture(const char* szFilePath) {
    int componentsPerPixel = BytesPerPixel;
    auto imageData = stbi_load(szFilePath, &_width, &_height, &componentsPerPixel, componentsPerPixel);

    if (imageData != nullptr) {
        const int size = _width * _height * componentsPerPixel;
        _data = std::vector<unsigned char>(imageData, imageData + size);

        delete imageData;
    }
    else {
        _width = _height = 0;
    }
}

Color ImageTexture::value(float u, float v, const Vec3& p) const {
    if (_data.size() == 0) {
        return Color(0.0f, 1.0f, 1.0f);
    }

    // Transform u,v coordinates to an x,y image pixel
    u = Math::clampf(u, 0.0f, 1.0f);
    v = 1.0f - Math::clampf(v, 0.0f, 1.0f);

    const int x = Math::clampInt(static_cast<int>(u * _width), 0, _width - 1);
    const int y = Math::clampInt(static_cast<int>(v * _height), 0, _height - 1);

    const float scale = 1.0f / 255.0f;
    const int stride = BytesPerPixel * _width;

    const auto pixel = _data.data() + ((y*stride) + (x*BytesPerPixel));

    return Color(pixel[0]*scale, pixel[1]*scale, pixel[2]*scale);
}
