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
            _values[i] = Vec3::normalize(Vec3::random(-1.0f, 1.0f));
            _permutationsX[i] = i;
            _permutationsY[i] = i;
            _permutationsZ[i] = i;
        }

        permute(_permutationsX);
        permute(_permutationsX);
        permute(_permutationsX);
    }

    float noise(const Vec3& p) const {
        const float u = p.x - floor(p.x);
        const float v = p.y - floor(p.y);
        const float w = p.z - floor(p.z);

        // Trilinear interpolation
        const int i = static_cast<int>(floor(p.x));
        const int j = static_cast<int>(floor(p.y));
        const int k = static_cast<int>(floor(p.z));
        Vec3 samples[2][2][2];

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

        // Hermitian smoothing
        const float uu = u*u*(3-2*u);
        const float vv = v*v*(3-2*v);
        const float ww = w*w*(3-2*w);

        float result = 0.0f;
        for (int di = 0; di < 2; di++) {
            for (int dj = 0; dj < 2; dj++) {
                for (int dk = 0; dk < 2; dk++) {
                    const Vec3 weight(u-di, v-dj, w-dk);
                    result += (di*uu + (1-di)*(1-uu))
                            * (dj*vv + (1-dj)*(1-vv))
                            * (dk*ww + (1-dk)*(1-ww))
                            * Vec3::dot(samples[di][dj][dk], weight);
                }
            }
        }

        return result;
    }

    float turbulence(const Vec3& p, int depth=7) const {
        float result = 0.0f;
        float weight = 1.0;
        Vec3 tmp = p;

        for (int i = 0; i < depth; i++) {
            result += weight * noise(tmp);
            weight *= 0.5;
            tmp *= 2.0f;
        }

        return fabs(result);
    }

private:
    std::vector<Vec3>  _values;
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
