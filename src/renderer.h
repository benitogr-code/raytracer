#pragma once

#include "common/imageBuffer.h"

class Scene;
class Camera;
struct Ray;

namespace Renderer {
    struct Settings {
        int imageWidth;
        int imageHeight;
        int samplesPerPixel;
        int maxBounces;
    };

    ImageBufferPtr render(const Scene& scene, const Camera& camera, const Settings& settings);
    void savePng(const ImageBufferPtr& image, const char* szFile);
};
