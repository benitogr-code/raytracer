#include <iostream>
#include <sstream>

#include "common/color.h"
#include "common/geometry.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "scene/SphereEntity.h"

std::string colorToString(const ColorRGB& c) {
    std::stringstream ss;

    int r = static_cast<int>(256 * Math::clampf(c.r, 0.0f, 0.99999f));
    int g = static_cast<int>(256 * Math::clampf(c.g, 0.0f, 0.99999f));
    int b = static_cast<int>(256 * Math::clampf(c.b, 0.0f, 0.99999f));

    ss << r << ' ' << g << ' ' << b;

    return ss.str();
}

Vec3 randUnitVector() {
    const float a = Math::randf(0.0f, 2.0f*Math::Pi);
    const float z = Math::randf(-1.0f, 1.0f);
    const float r = sqrt(1.0f - z*z);

    return Vec3(r*cos(a), r*sin(a), z);
}

ColorRGB gamma2(const ColorRGB& c) {
    return ColorRGB(sqrt(c.r), sqrt(c.g), sqrt(c.b));
}

ColorRGB rayTrace(const Scene& scene, const Ray& ray, int bounces) {
    if (bounces <= 0)
        return ColorRGB(0.0f, 0.0f, 0.0f);

    HitInfo hit;
    if (scene.rayTrace(ray, 0.0025f, Math::MaxFloat, hit)) {
        const Vec3 randUnit = randUnitVector();
        const Vec3 reflectTarget = hit.point + hit.normal + randUnit;

        return 0.5f*rayTrace(scene, Ray(hit.point, Vec3::normalize(reflectTarget - hit.point)), bounces-1);
    }

    const float t = 0.5f*(ray.direction.y + 1.0f);

    return (1.0f-t)*ColorRGB(1.0f, 1.0f, 1.0f) + t*ColorRGB(0.5f, 0.7f, 1.0f);
}

int main() {
    // Image
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 640;
    const int imageHeight = (int)(imageWidth / aspectRatio);

    const int perPixelSamples = 16;
    const int maxBounces = 10;

    // Camera
    const Camera camera(aspectRatio);

    // Scene
    Scene scene;
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f)
    ));
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f)
    ));

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int y = imageHeight-1; y >= 0; --y) {
        std::cerr << "Scanning line: " << (imageHeight-y) << std::endl;

        for (int x = 0; x < imageWidth; ++x) {
            ColorRGB pixel(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < perPixelSamples; ++s) {
                const float u = float(x + Math::randf()) / (imageWidth-1);
                const float v = float(y + Math::randf()) / (imageHeight-1);

                const Ray ray = camera.viewportRay(u, v);
                pixel += rayTrace(scene, ray, maxBounces);
            }

            const float scale = 1.0f / perPixelSamples;
            std::cout << colorToString(gamma2(pixel*scale)) << '\n';
        }
    }

    return 0;
}
