#include <iostream>

#include "common/color.h"
#include "common/geometry.h"
#include "common/imageBuffer.h"
#include "scene/materials/dielectric.h"
#include "scene/materials/lambertian.h"
#include "scene/materials/metal.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/entitySphere.h"
#include "renderer.h"

enum class SceneID {
    Spheres,
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

void buildSceneSpheres(Scene& scene) {
    IMaterialPtr materialGround = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
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
    Scene scene;
    buildScene(sceneId, scene);

    const float aspectRatio = 16.0f / 9.0f;

    const Vec3 camPos(13.0f, 2.0f, 3.0f);
    const Vec3 camTarget(0.0f, 0.0f, 0.0f);
    const float focusDistance = 10.0f;
    const float aperture = 0.1f;
    const float shutterTime = 0.4f;

    Camera camera(25.0f, aspectRatio, aperture, focusDistance, shutterTime);
    camera.lookAt(camPos, camTarget);

    // Render image
    Renderer::Settings settings;
    settings.imageWidth = 480;
    settings.imageHeight = (int)(480 / aspectRatio);
    settings.samplesPerPixel = 8;
    settings.maxBounces = 5;

    std::cout << "Rendering scene..." << std::endl;

    auto image = Renderer::render(scene, camera, settings);

    const char* szOutFile = getFilePathForScene(sceneId);
    std::cout << "\nSaving to " << szOutFile << std::endl;

    Renderer::savePng(image, szOutFile);

    std::cout << "Finished" << std::endl;

    return 0;
}
