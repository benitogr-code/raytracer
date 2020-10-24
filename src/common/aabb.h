#pragma once

#include "vector.h"

struct Ray;

class AABB {
public:
    AABB() {};
    AABB(const Vec3& min, const Vec3& max)
        : _min(min)
        , _max(max) {}

    inline const Vec3& min() const { return _min; }
    inline const Vec3& max() const { return _max; }

    bool hit(const Ray& ray, float tMin, float tMax) const;

    static AABB surroundingBox(const AABB& box0, const AABB& box1);

private:
    Vec3 _min;
    Vec3 _max;
};
