#pragma once

#include <vector>

#include "math.h"
#include "vector.h"

class Perlin {
private:
    enum {
        PointCount = 256,
        Mask = 255
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
        float u = p.x - floor(p.x);
        float v = p.y - floor(p.y);
        float w = p.z - floor(p.z);

        // Hermitian smoothing
        u = u*u*(3-2*u);
        v = v*v*(3-2*v);
        w = w*w*(3-2*w);

        // Trilinear interpolation
        const int i = static_cast<int>(floor(p.x));
        const int j = static_cast<int>(floor(p.y));
        const int k = static_cast<int>(floor(p.z));
        float samples[2][2][2];

        for (int di = 0; di < 2; di++) {
            for (int dj = 0; dj < 2; dj++) {
                for (int dk = 0; dk < 2; dk++) {
                    samples[di][dj][dk] = _values[
                            _permutationsX[(i+di) & Mask] ^
                            _permutationsY[(j+dj) & Mask] ^
                            _permutationsZ[(k+dk) & Mask]
                        ];
                }
            }
        }

        float result = 0.0f;
        for (int di = 0; di < 2; di++) {
            for (int dj = 0; dj < 2; dj++) {
                for (int dk = 0; dk < 2; dk++) {
                    result += (di*u + (1-di)*(1-u))*
                                (dj*v + (1-dj)*(1-v))*
                                (dk*w + (1-dk)*(1-w))*
                                samples[di][dj][dk];
                }
            }
        }

        return result;
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
