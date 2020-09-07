#pragma once

#include "common/imageBuffer.h"

class Scene;
class Camera;
struct Ray;

struct RenderSettings {
    int imageWidth;
    int imageHeight;
    int samplesPerPixel;
    int maxBounces;
};

class Renderer {
public:
    ImageBufferPtr render(const Scene& scene, const Camera& camera, const RenderSettings& settings) const;
};
