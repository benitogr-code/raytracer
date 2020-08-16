cmake_minimum_required (VERSION 3.1)

project (pathtracer)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/)

include_directories ("${PROJECT_SOURCE_DIR}/src")

set(APP_SOURCES
	src/main.cpp
)

add_executable(pathtracer
	${APP_SOURCES}
)