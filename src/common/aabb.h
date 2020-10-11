#pragma once

#include "geometry.h"

class AABB {
public:
    AABB() {};
    AABB(const Vec3& min, const Vec3& max)
        : _min(min)
        , _max(max) {}

    inline const Vec3& min() const { return _min; }
    inline const Vec3& max() const { return _max; }

    bool hit(const Ray& ray, float tMin, float tMax) const {
        for (int axis = 0; axis < 3; axis++) {
            const float invDir = 1.0f / ray.direction._v[axis];
            const float diffMin = _min._v[axis] - ray.origin._v[axis];
            const float diffMax = _max._v[axis] - ray.origin._v[axis];

            const float t0 = Math::min(diffMin * invDir, diffMax * invDir);
            const float t1 = Math::max(diffMin * invDir, diffMax * invDir);

            tMin = Math::max(t0, tMin);
            tMax = Math::min(t1, tMax);

            if (tMax <= tMin)
                return false;
        }

        return true;
    }

    static AABB surroundingBox(const AABB& box0, const AABB& box1) {
        const Vec3 min(
            Math::min(box0.min().x, box1.min().x),
            Math::min(box0.min().y, box1.min().y),
            Math::min(box0.min().z, box1.min().z)
        );
        const Vec3 max(
            Math::max(box0.max().x, box1.max().x),
            Math::max(box0.max().y, box1.max().y),
            Math::max(box0.max().z, box1.max().z)
        );

        return AABB(min, max);
    }

private:
    Vec3 _min;
    Vec3 _max;
};
