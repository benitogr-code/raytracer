#pragma once

#include <vector>

#include "math.h"
#include "vector.h"

class Perlin {
private:
    enum {
        PointCount = 256,
        PointMask = 255
    };

public:
    Perlin() {
        _values.resize(PointCount);
        _permutationsX.resize(PointCount);
        _permutationsY.resize(PointCount);
        _permutationsZ.resize(PointCount);

        for (int i = 0; i < PointCount; ++i) {
            _values[i] = Math::randf();
            _permutationsX[i] = i;
            _permutationsY[i] = i;
            _permutationsZ[i] = i;
        }

        permute(_permutationsX);
        permute(_permutationsX);
        permute(_permutationsX);
    }

    float noise(const Vec3& p) const {
        const int i = static_cast<int>(4.0f*p.x) & PointMask;
        const int j = static_cast<int>(4.0f*p.y) & PointMask;
        const int k = static_cast<int>(4.0f*p.z) & PointMask;

        return _values[_permutationsX[i] ^ _permutationsY[j] ^ _permutationsZ[k]];
    }

private:
    std::vector<float> _values;
    std::vector<int>   _permutationsX;
    std::vector<int>   _permutationsY;
    std::vector<int>   _permutationsZ;

    static void permute(std::vector<int>& p) {
        for (int i = p.size()-1; i > 0; i--) {
            const int target = Math::randInt(0, i);
            const int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }
};
