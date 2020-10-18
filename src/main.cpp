#include <iostream>

#include "common/color.h"
#include "common/geometry.h"
#include "common/imageBuffer.h"
#include "scene/materials/dielectric.h"
#include "scene/materials/lambertian.h"
#include "scene/materials/metal.h"
#include "scene/textures/checker.h"
#include "scene/textures/noise.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/entitySphere.h"
#include "renderer.h"

enum class SceneID {
    RandomSpheres,
    PerlinSpheres,
};

enum class Quality {
    Low,
    Medium,
    High
};

SceneID parseScene(int argc, char* argv[]) {
    const char* scene = "";

    for (int i = 0; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--scene") == 0) {
            scene = argv[i+1];
            break;
        }
    }

    if (strcmp(scene, "perlin-spheres") == 0) {
        return SceneID::PerlinSpheres;
    }

    return SceneID::RandomSpheres;
}

Quality parseQuality(int argc, char* argv[]) {
    const char* quality = "";

    for (int i = 0; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--quality") == 0) {
            quality = argv[i+1];
            break;
        }
    }

    if (strcmp(quality, "high") == 0) {
        return Quality::High;
    }

    if (strcmp(quality, "medium") == 0) {
        return Quality::Medium;
    }

    return Quality::Low;
}

void randomSpheres(std::vector<IHittablePtr>& entities) {
    entities.clear();

    ITexturePtr checker = std::make_shared<Checker>(Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));
    IMaterialPtr materialGround = std::make_shared<Lambertian>(checker);

    entities.push_back(std::make_shared<EntitySphere>(
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
            Vec3 velocity(0.0f, 0.0f, 0.0f);

            if ((position - Vec3(4.0f, 0.2f, 0.0f)).length() < 0.9f)
                continue;

            IMaterialPtr materialSphere;

            const float selection = Math::randf();
            if (selection < 0.8f) {
                const Color albedo = Color::random() * Color::random();
                materialSphere = std::make_shared<Lambertian>(albedo);
                velocity.y = Math::randf(0.0f, 0.5f);
            }
            else if (selection < 0.95f) {
                const Color albedo = Color::random(0.5f, 1.0f);
                const float fuzz = Math::randf(0.0f, 0.5f);
                materialSphere = std::make_shared<Metal>(albedo, fuzz);
            } else {
                materialSphere = std::make_shared<Dielectric>(1.5f);
            }

            auto sphere = std::make_shared<EntitySphere>(Sphere(position, 0.2f), materialSphere);
            sphere->setVelocity(velocity);
            entities.push_back(sphere);
        }
    }

    IMaterialPtr material1 = std::make_shared<Dielectric>(1.5f);
    entities.push_back(std::make_shared<EntitySphere>(
        Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        material1
    ));

    IMaterialPtr material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    entities.push_back(std::make_shared<EntitySphere>(
        Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f),
        material2
    ));

    IMaterialPtr material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    entities.push_back(std::make_shared<EntitySphere>(
        Sphere(Vec3(4.0f, 1.0f, 0.0f), 1.0f),
        material3
    ));
}

void perlinSpheres(std::vector<IHittablePtr>& entities) {
    entities.clear();

    auto texture = std::make_shared<Noise>(4.0f);

    entities.push_back(std::make_shared<EntitySphere>(
        Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f),
        std::make_shared<Lambertian>(texture)
    ));
    entities.push_back(std::make_shared<EntitySphere>(
        Sphere(Vec3(0.0f, 2.0f, 0.0f), 2.0f),
        std::make_shared<Lambertian>(texture)
    ));
}

const char* getFilePathForScene(SceneID id) {
    if (id == SceneID::RandomSpheres) {
        return ".output/random-spheres.png";
    }

    if (id == SceneID::PerlinSpheres) {
        return ".output/perlin-spheres.png";
    }

    return ".output/image.png";
}

int main(int argc, char* argv[]) {
    const SceneID sceneId = parseScene(argc, argv);
    const Quality quality = parseQuality(argc, argv);

    const float aspectRatio = 16.0f / 9.0f;

    Vec3 camPos;
    Vec3 camTarget;
    float focusDistance = 10.0f;
    float aperture = 0.0f;
    float shutterTime = 0.4f;
    float vFov = 25.0f;

    std::vector<IHittablePtr> entities;
    if (sceneId == SceneID::RandomSpheres) {
        camPos = Vec3(13.0f, 2.0f, 3.0f);
        camTarget = Vec3(0.0f, 0.0f, 0.0f);
        aperture = 0.1f;

        randomSpheres(entities);
    }
    else if (sceneId == SceneID::PerlinSpheres) {
        camPos = Vec3(13.0f, 2.0f, 3.0f);
        camTarget = Vec3(0.0f, 0.0f, 0.0f);
        vFov = 20.0f;

        perlinSpheres(entities);
    }

    Camera camera(vFov, aspectRatio, aperture, focusDistance, shutterTime);
    camera.lookAt(camPos, camTarget);

    Scene scene;
    scene.build(entities, 0.0f, camera.shutterTime());

    // Render image
    Renderer::Settings settings;
    if (quality == Quality::High) {
        const int width = 1024;
        settings.imageWidth = width;
        settings.imageHeight = (int)(width / aspectRatio);
        settings.samplesPerPixel = 256;
        settings.maxBounces = 16;
    }
    else if (quality == Quality::Medium) {
        const int width = 720;
        settings.imageWidth = width;
        settings.imageHeight = (int)(width / aspectRatio);
        settings.samplesPerPixel = 32;
        settings.maxBounces = 8;
    }
    else {
        const int width = 480;
        settings.imageWidth = width;
        settings.imageHeight = (int)(width / aspectRatio);
        settings.samplesPerPixel = 8;
        settings.maxBounces = 4;
    }

    std::cout << "Rendering scene..." << std::endl;

    auto image = Renderer::render(scene, camera, settings);

    const char* szOutFile = getFilePathForScene(sceneId);
    std::cout << "\nSaving to " << szOutFile << std::endl;

    Renderer::savePng(image, szOutFile);

    std::cout << "Finished" << std::endl;

    return 0;
}
