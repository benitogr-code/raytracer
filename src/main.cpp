#include <iostream>

#include "common/color.h"
#include "common/geometry.h"
#include "common/imageBuffer.h"
#include "scene/materials/dielectric.h"
#include "scene/materials/lambertian.h"
#include "scene/materials/metal.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/sphereEntity.h"
#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "common/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "common/stb/stb_image_write.h"

void savePng(const char* szFile, const ImageBufferPtr imgBuffer) {
    const int stride = imgBuffer->width() * imgBuffer->channels();
    const unsigned char* end = imgBuffer->data() + (imgBuffer->width() * imgBuffer->channels() * (imgBuffer->height() - 1));
    stbi_write_png(szFile, imgBuffer->width(), imgBuffer->height(), imgBuffer->channels(), end, -stride);
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
    // Scene & camera
    Scene scene;
    buildScene(scene);

    const float aspectRatio = 16.0f / 9.0f;

    const Vec3 camPos(13.0f, 2.0f, 3.0f);
    const Vec3 camTarget(0.0f, 0.0f, 0.0f);
    const float focusDistance = 10.0f;
    const float aperture = 0.1f;

    Camera camera(25.0f, aspectRatio, aperture, focusDistance);
    camera.lookAt(camPos, camTarget);

    // Render image
    RenderSettings settings;
    settings.imageWidth = 480;
    settings.imageHeight = (int)(480 / aspectRatio);
    settings.samplesPerPixel = 8;
    settings.maxBounces = 5;

    std::cout << "Rendering scene..." << std::endl;
    {
        Renderer renderer;
        auto imgBuffer = renderer.render(scene, camera, settings);

        const char* szFile = ".output/image.png";
        std::cout << "\nSaving to " << szFile << std::endl;

        savePng(szFile, imgBuffer);
    }
    std::cout << "Finished" << std::endl;

    return 0;
}
