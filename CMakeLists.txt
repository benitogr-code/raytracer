cmake_minimum_required (VERSION 3.1)

project (raytracer)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/)

include_directories ("${PROJECT_SOURCE_DIR}/src")

set(APP_SOURCES
    src/common/stb/stb_image.h
    src/common/stb/stb_image_write.h
    src/common/aabb.h
    src/common/aabb.cpp
    src/common/color.h
    src/common/hittable.h
    src/common/imageBuffer.h
    src/common/material.h
    src/common/math.h
    src/common/matrix.h
    src/common/perlin.h
    src/common/stbHelper.h
    src/common/stbHelper.cpp
    src/common/texture.h
    src/common/vector.h
    src/scene/materials/dielectric.h
    src/scene/materials/dielectric.cpp
    src/scene/materials/diffuseLight.h
    src/scene/materials/lambertian.h
    src/scene/materials/lambertian.cpp
    src/scene/materials/metal.h
    src/scene/materials/metal.cpp
    src/scene/textures/checker.h
    src/scene/textures/image.cpp
    src/scene/textures/image.h
    src/scene/textures/noise.h
    src/scene/textures/solidColor.h
    src/scene/bvh.h
    src/scene/bvh.cpp
    src/scene/camera.h
    src/scene/entity.h
    src/scene/entityBox.h
    src/scene/entityBox.cpp
    src/scene/entityRect.h
    src/scene/entityRect.cpp
    src/scene/entitySphere.h
    src/scene/entitySphere.cpp
    src/scene/scene.h
    src/main.cpp
    src/renderer.h
    src/renderer.cpp
)

add_executable(raytracer
    ${APP_SOURCES}
)
