#pragma once

#include <memory>
#include <vector>

#include "../common/hittable.h"

class BvhNode : public IHittable {
private:
    friend class BvhTree;

public:
    // IHittable
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const override;
    virtual bool getAABB(float t0, float t1, AABB& bbox) const override;
    //~IHittable

private:
    IHittablePtr _left;
    IHittablePtr _right;
    AABB _bbox;
};

typedef std::shared_ptr<BvhNode> BvhNodePtr;

class BvhTree {
public:
    BvhTree(const std::vector<IHittablePtr>& entities, float t0, float t1);

    bool hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const;

private:
    BvhNodePtr build(const std::vector<IHittablePtr>& entities, size_t start, size_t end, float t0, float t1);

private:
    BvhNodePtr _root;
};

typedef std::shared_ptr<BvhTree> BvhTreePtr;
