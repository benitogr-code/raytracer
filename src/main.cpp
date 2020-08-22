#include <iostream>
#include <sstream>

#include "common/color.h"
#include "common/geometry.h"
#include "scene/materials/lambertian.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/sphereEntity.h"

std::string colorToString(const Color& c) {
    std::stringstream ss;

    int r = static_cast<int>(256 * Math::clampf(c.r, 0.0f, 0.99999f));
    int g = static_cast<int>(256 * Math::clampf(c.g, 0.0f, 0.99999f));
    int b = static_cast<int>(256 * Math::clampf(c.b, 0.0f, 0.99999f));

    ss << r << ' ' << g << ' ' << b;

    return ss.str();
}

Color gamma2(const Color& c) {
    return Color(sqrt(c.r), sqrt(c.g), sqrt(c.b));
}

Color rayTrace(const Scene& scene, const Ray& ray, int bounces) {
    if (bounces <= 0)
        return Color(0.0f, 0.0f, 0.0f);

    HitInfo hit;
    if (scene.rayTrace(ray, 0.0025f, Math::MaxFloat, hit)) {
        Ray scattered;
        Color attenuation;
        if (!hit.material->scatter(ray, hit, attenuation, scattered))
            return Color(0.0f, 0.0f, 0.0f);

        return attenuation * rayTrace(scene, scattered, bounces-1);
    }

    const float t = 0.5f*(ray.direction.y + 1.0f);

    return (1.0f-t)*Color(1.0f, 1.0f, 1.0f) + t*Color(0.5f, 0.7f, 1.0f);
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
    auto materialGround = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    auto materialSphere = std::make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));

    Scene scene;
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f),
        materialSphere
    ));
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f),
        materialGround
    ));

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int y = imageHeight-1; y >= 0; --y) {
        std::cerr << "Scanning line: " << (imageHeight-y) << std::endl;

        for (int x = 0; x < imageWidth; ++x) {
            Color pixel(0.0f, 0.0f, 0.0f);

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