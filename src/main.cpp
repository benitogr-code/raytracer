#include <iostream>
#include <sstream>

#include "common/color.h"
#include "common/geometry.h"
#include "common/imageBuffer.h"
#include "scene/materials/dielectric.h"
#include "scene/materials/lambertian.h"
#include "scene/materials/metal.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/sphereEntity.h"

#define STB_IMAGE_IMPLEMENTATION
#include "common/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "common/stb/stb_image_write.h"

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

void savePng(const char* szFile, const ImageBuffer& imgBuffer) {
    const int stride = imgBuffer.width() * imgBuffer.channels();
    const unsigned char* end = imgBuffer.data() + (imgBuffer.width() * imgBuffer.channels() * (imgBuffer.height() - 1));
    stbi_write_png(szFile, imgBuffer.width(), imgBuffer.height(), imgBuffer.channels(), end, -stride);
}

Color gamma2(const Color& c) {
    return Color(sqrt(c.r), sqrt(c.g), sqrt(c.b));
}

Color rayTrace(const Scene& scene, const Ray& ray, int bounces) {
    if (bounces <= 0)
        return Color(0.0f, 0.0f, 0.0f);

    HitInfo hit;
    if (scene.rayTrace(ray, 0.005f, Math::MaxFloat, hit)) {
        Ray scattered;
        Color attenuation;
        if (!hit.material->scatter(ray, hit, attenuation, scattered))
            return Color(0.0f, 0.0f, 0.0f);

        return attenuation * rayTrace(scene, scattered, bounces-1);
    }

    const float t = 0.5f*(ray.direction.y + 1.0f);

    return (1.0f-t)*Color(1.0f, 1.0f, 1.0f) + t*Color(0.5f, 0.7f, 1.0f);
}

void buildScene(Scene& scene) {
    IMaterialPtr materialGround = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f),
        materialGround
    ));

    for (int i = -11; i < 11; i++) {
        for (int j = -11; j < 11; j++) {
            const Vec3 position(
                i + 0.9f*Math::randf(),
                0.2f,
                j + 0.9f*Math::randf()
            );

            if ((position - Vec3(4.0f, 0.2f, 0.0f)).length() < 0.9f)
                continue;

            IMaterialPtr materialSphere;

            const float selection = Math::randf();
            if (selection < 0.8f) {
                const Color albedo = Color::random() * Color::random();
                materialSphere = std::make_shared<Lambertian>(albedo);
            }
            else if (selection < 0.95f) {
                const Color albedo = Color::random(0.5f, 1.0f);
                const float fuzz = Math::randf(0.0f, 0.5f);
                materialSphere = std::make_shared<Metal>(albedo, fuzz);
            } else {
                materialSphere = std::make_shared<Dielectric>(1.5f);
            }

            scene.addEntity(std::make_shared<SphereEntity>(
                Sphere(position, 0.2f),
                materialSphere
            ));
        }
    }

    IMaterialPtr material1 = std::make_shared<Dielectric>(1.5f);
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        material1
    ));

    IMaterialPtr material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f),
        material2
    ));

    IMaterialPtr material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene.addEntity(std::make_shared<SphereEntity>(
        Sphere(Vec3(4.0f, 1.0f, 0.0f), 1.0f),
        material3
    ));
}

int main() {
    // Scene & vamera
    Scene scene;
    buildScene(scene);

    // Settings
    const float aspectRatio = 16.0f / 9.0f;
    const int perPixelSamples = 8;
    const int maxBounces = 5;

    const Vec3 camPos(13.0f, 2.0f, 3.0f);
    const Vec3 camTarget(0.0f, 0.0f, 0.0f);
    const float focusDistance = 10.0f;
    const float aperture = 0.1f;

    Camera camera(25.0f, aspectRatio, aperture, focusDistance);
    camera.lookAt(camPos, camTarget);

    // Render image
    const int imageWidth = 480;
    const int imageHeight = (int)(imageWidth / aspectRatio);
    ImageBuffer imgBuffer(imageWidth, imageHeight);

    std::cout << "Rendering scene..." << std::endl;

    for (int y = imageHeight-1; y >= 0; --y) {
        const float progress = ((float)(imageHeight-y) / imageHeight);
        displayProgress(progress);

        for (int x = 0; x < imageWidth; ++x) {
            Color pixel(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < perPixelSamples; ++s) {
                const float u = float(x + Math::randf()) / (imageWidth-1);
                const float v = float(y + Math::randf()) / (imageHeight-1);

                const Ray ray = camera.viewportRay(u, v);
                pixel += rayTrace(scene, ray, maxBounces);
            }

            const float scale = 1.0f / perPixelSamples;
            imgBuffer.writePixel(x, y, gamma2(pixel*scale));
        }
    }

    const char* szFile = ".output/image.png";
    std::cout << "\nSaving to " << szFile << std::endl;

    savePng(szFile, imgBuffer);

    std::cout << "Finished" << std::endl;

    return 0;
}
