#include <iostream>
#include <sstream>

#include "common/color.h"
#include "common/geometry.h"

std::string colorToString(const ColorRGB& c) {
    std::stringstream ss;

    int r = static_cast<int>(255.999f * c.r);
    int g = static_cast<int>(255.999f * c.g);
    int b = static_cast<int>(255.999f * c.b);

    ss << r << ' ' << g << ' ' << b;

    return ss.str();
}

ColorRGB rayToColor(const Ray& r) {
    const Vec3 rayDir = Vec3::normalize(r.direction);
    const float t = 0.5f*(rayDir.y + 1.0f);

    return (1.0f-t)*ColorRGB(1.0f, 1.0f, 1.0f) + t*ColorRGB(0.5f, 0.7f, 1.0f);
}

int main() {
    // Image
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 1280;
    const int imageHeight = (int)(imageWidth / aspectRatio);

    // Camera
    const float viewPortHeight = 2.0f;
    const float viewPortWidth = viewPortHeight * aspectRatio;
    const float focalLength = 1.0f;

    const Vec3 origin(0.0f, 0.0f, 0.0f);
    const Vec3 horizontal(viewPortWidth, 0.0f, 0.0f);
    const Vec3 vertical(0.0f, viewPortHeight, 0.0f);
    const Vec3 viewPortBottomLeft = origin - Vec3(viewPortWidth/2.0f, viewPortHeight/2.0f, focalLength);

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int y = imageHeight-1; y >= 0; --y) {
        std::cerr << "Scanning line: " << (imageHeight-y) << std::endl;
        for (int x = 0; x < imageWidth; ++x) {
            const float u = float(x) / (imageWidth-1);
            const float v = float(y) / (imageHeight-1);

            const Ray ray(origin, viewPortBottomLeft + u*horizontal + v*vertical - origin);
            const ColorRGB pixelColor = rayToColor(ray);

            std::cout << colorToString(pixelColor) << '\n';
        }
    }

    return 0;
}
