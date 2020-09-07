#include "renderer.h"
#include "scene/camera.h"
#include "scene/scene.h"

#include <iostream>
#include <sstream>

void displayProgress(float value) {
    const int barWidth = 60;
    const int pos = barWidth * value;

    std::stringstream ss;
    ss << "\rProgress [";

    for (int i = 0; i < barWidth; ++i) {
        ss << ((i <= pos) ? "*" : " ");
    }

    ss << "] " << int(value * 100.0f) << " %";

    std::cout << ss.str() << std::flush;
}

Color raytrace(const Scene& scene, const Ray& ray, int bounces) {
    if (bounces <= 0)
        return Color(0.0f, 0.0f, 0.0f);

    HitInfo hit;
    if (scene.rayTrace(ray, 0.005f, Math::MaxFloat, hit)) {
        Ray scattered;
        Color attenuation;
        if (!hit.material->scatter(ray, hit, attenuation, scattered))
            return Color(0.0f, 0.0f, 0.0f);

        return attenuation * raytrace(scene, scattered, bounces-1);
    }

    const float t = 0.5f*(ray.direction.y + 1.0f);

    return (1.0f-t)*Color(1.0f, 1.0f, 1.0f) + t*Color(0.5f, 0.7f, 1.0f);
}

Color gamma2(const Color& c) {
    return Color(sqrt(c.r), sqrt(c.g), sqrt(c.b));
}

ImageBufferPtr Renderer::render(const Scene& scene, const Camera& camera, const RenderSettings& settings) const {
    auto buffer = std::make_shared<ImageBuffer>(settings.imageWidth, settings.imageHeight);

    for (int y = settings.imageHeight-1; y >= 0; --y) {
        const float progress = ((float)(settings.imageHeight-y) / settings.imageHeight);
        displayProgress(progress);

        for (int x = 0; x < settings.imageWidth; ++x) {
            Color pixel(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < settings.samplesPerPixel; ++s) {
                const float u = float(x + Math::randf()) / (settings.imageWidth-1);
                const float v = float(y + Math::randf()) / (settings.imageHeight-1);

                const Ray ray = camera.viewportRay(u, v);
                pixel += raytrace(scene, ray, settings.maxBounces);
            }

            const float scale = 1.0f / settings.samplesPerPixel;
            buffer->writePixel(x, y, gamma2(pixel*scale));
        }
    }

    return buffer;
}
