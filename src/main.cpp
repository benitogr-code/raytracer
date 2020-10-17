#include <iostream>

#include "common/color.h"
#include "common/geometry.h"
#include "common/imageBuffer.h"
#include "scene/materials/dielectric.h"
#include "scene/materials/lambertian.h"
#include "scene/materials/metal.h"
#include "scene/textures/checkerTexture.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/entitySphere.h"
#include "renderer.h"

enum class SceneID {
    Spheres,
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

    // Check for other scenes here

    return SceneID::Spheres;
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

void buildSceneSpheres(Scene& scene) {
    ITexturePtr checker = std::make_shared<CheckerTexture>(Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));
    IMaterialPtr materialGround = std::make_shared<Lambertian>(checker);
    scene.addEntity(std::make_shared<EntitySphere>(
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
            scene.addEntity(sphere);
        }
    }

    IMaterialPtr material1 = std::make_shared<Dielectric>(1.5f);
    scene.addEntity(std::make_shared<EntitySphere>(
        Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        material1
    ));

    IMaterialPtr material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    scene.addEntity(std::make_shared<EntitySphere>(
        Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f),
        material2
    ));

    IMaterialPtr material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        scene.addEntity(std::make_shared<EntitySphere>(
        Sphere(Vec3(4.0f, 1.0f, 0.0f), 1.0f),
        material3
    ));
}

void buildScene(SceneID id, Scene& outScene) {
    if (id == SceneID::Spheres) {
        std::cout << "Building scene: Spheres" << std::endl;
        buildSceneSpheres(outScene);
    }
}

const char* getFilePathForScene(SceneID id) {
    if (id == SceneID::Spheres) {
        return ".output/spheres.png";
    }

    return ".output/image.png";
}

int main(int argc, char* argv[]) {
    // Scene & camera
    const SceneID sceneId = parseScene(argc, argv);
    const Quality quality = parseQuality(argc, argv);

    const float aspectRatio = 16.0f / 9.0f;

    const Vec3 camPos(13.0f, 2.0f, 3.0f);
    const Vec3 camTarget(0.0f, 0.0f, 0.0f);
    const float focusDistance = 10.0f;
    const float aperture = 0.1f;
    const float shutterTime = 0.4f;

    Camera camera(25.0f, aspectRatio, aperture, focusDistance, shutterTime);
    camera.lookAt(camPos, camTarget);

    Scene scene;
    buildScene(sceneId, scene);
    scene.buildBvh(0.0f, shutterTime);

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
