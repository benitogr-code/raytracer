cmake_minimum_required (VERSION 3.1)

project (raytracer)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/)

include_directories ("${PROJECT_SOURCE_DIR}/src")

set(APP_SOURCES
	src/common/color.h
	src/common/geometry.h
	src/common/math.h
	src/scene/IEntity.h
	src/scene/Scene.h
	src/scene/Scene.cpp
	src/scene/SphereEntity.h
	src/scene/SphereEntity.cpp
	src/main.cpp
)

add_executable(raytracer
	${APP_SOURCES}
)
