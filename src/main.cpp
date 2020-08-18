#include <iostream>
#include <sstream>

#include "common/color.h"

std::string colorToString(const ColorRGB& c) {
    std::stringstream ss;

    int r = static_cast<int>(255.999f * c.r);
    int g = static_cast<int>(255.999f * c.g);
    int b = static_cast<int>(255.999f * c.b);

    ss << r << ' ' << g << ' ' << b;

    return ss.str();
}

int main() {

    // Image
    const int imageWidth = 256;
    const int imageHeight = 256;

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int y = imageHeight-1; y >= 0; --y) {
        for (int x = 0; x < imageWidth; ++x) {
            ColorRGB pixelColor(
                float(x) / (imageWidth-1),
                float(y) / (imageHeight-1),
                0.25f
            );
            std::cout << colorToString(pixelColor) << '\n';
        }
    }

    return 0;
}
