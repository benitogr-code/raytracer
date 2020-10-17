cmake_minimum_required (VERSION 3.1)

project (raytracer)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/)

include_directories ("${PROJECT_SOURCE_DIR}/src")

set(APP_SOURCES
	src/common/stb/stb_image.h
	src/common/stb/stb_image_write.h
	src/common/color.h
	src/common/geometry.h
	src/common/hittable.h
	src/common/imageBuffer.h
	src/common/material.h
	src/common/math.h
	src/common/vector.h
	src/scene/materials/dielectric.h
	src/scene/materials/dielectric.cpp
	src/scene/materials/lambertian.h
	src/scene/materials/lambertian.cpp
	src/scene/materials/metal.h
	src/scene/materials/metal.cpp
	src/scene/bvh.h
	src/scene/bvh.cpp
	src/scene/camera.h
	src/scene/entity.h
	src/scene/entitySphere.h
	src/scene/entitySphere.cpp
	src/scene/scene.h
	src/scene/scene.cpp
	src/main.cpp
	src/renderer.h
	src/renderer.cpp
)

add_executable(raytracer
	${APP_SOURCES}
)
