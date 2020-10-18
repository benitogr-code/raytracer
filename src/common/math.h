#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace Math {
    const float MaxFloat = std::numeric_limits<float>::infinity();
    const float Pi = 3.1415926535897932385f;

    template<typename T>
    inline bool inRange(const T& value, const T& min, const T& max) {
        return (value > min) && (value < max);
    }

    template<typename T>
    inline float min(const T& a, const T& b) {
        return std::min<T>(a, b);
    }

    template<typename T>
    inline float max(const T& a, const T& b) {
        return std::max<T>(a, b);
    }

    inline float randf() {
        return (float)rand() / (float)(RAND_MAX + 1.0f);
    }

    inline float randf(float min, float max) {
        return min + (max-min)*randf();
    }

    inline int randInt(int min, int max) {
        return static_cast<int>(randf(min, max+1));
    }

    inline float clampf(float value, float min, float max) {
        return std::max(min, std::min(value, max));
    }

    inline float degreesToRadians(float value) {
        return (value * Pi) / 180.0f;
    }

    inline float schlick(float cosine, float refractionIndex) {
        float r0 = (1-refractionIndex) / (1+refractionIndex);
        r0 *= r0;

        return r0 + (1.0f-r0)*pow((1.0f - cosine),5);
    }
}
