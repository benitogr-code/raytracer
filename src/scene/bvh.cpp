#include "bvh.h"

#include <algorithm>

inline bool bboxCompare(const IHittablePtr& a, const IHittablePtr& b, int axis) {
    AABB bboxA;
    AABB bboxB;

    if (!a->getAABB(0.0f, 0.0f, bboxA) || !b->getAABB(0.0f, 0.0f, bboxB))
        throw "Error building Bvh";

    return bboxA.min()._v[axis] < bboxB.min()._v[axis];
}


bool bboxCompareX(const IHittablePtr& a, const IHittablePtr& b) {
    return bboxCompare(a, b, 0);
}

bool bboxCompareY(const IHittablePtr& a, const IHittablePtr& b) {
    return bboxCompare(a, b, 1);
}

bool bboxCompareZ(const IHittablePtr& a, const IHittablePtr& b) {
    return bboxCompare(a, b, 2);
}

/// BvhNode

bool BvhNode::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    if (!_bbox.hit(ray, tMin, tMax))
        return false;

    const bool hitLeft = _left->hit(ray, tMin, tMax, outHit);
    const bool hitRight = _right->hit(ray, tMin, hitLeft ? outHit.t : tMax, outHit);

    return hitLeft || hitRight;
}

bool BvhNode::getAABB(float t0, float t1, AABB& bbox) const {
    bbox = _bbox;

    return true;
}

/// BvhTree

BvhTree::BvhTree(const std::vector<IHittablePtr>& entities, float t0, float t1) {
    const size_t start = 0;
    const size_t end = entities.size();

    if (start < end) {
        _root = build(entities, start, end, t0, t1);
    }
}

bool BvhTree::hit(const Ray& ray, float tMin, float tMax, HitInfo& outHit) const {
    return _root != nullptr ? _root->hit(ray, tMin, tMax, outHit) : false;
}

BvhNodePtr BvhTree::build(const std::vector<IHittablePtr>& entities, size_t start, size_t end, float t0, float t1) {
    const int axis = Math::randInt(0,2);
    auto comparator = (axis == 0) ? bboxCompareX
                    : (axis == 1) ? bboxCompareY
                                  : bboxCompareZ;

    const size_t span = end - start;

    BvhNodePtr node = std::make_shared<BvhNode>();

    if (span == 1) {
        node->_left = node->_right = entities[start];
    } else if (span == 2) {
        if (comparator(entities[start], entities[start+1])) {
            node->_left = entities[start];
            node->_right = entities[start+1];
        } else {
            node->_left = entities[start+1];
            node->_right = entities[start];
        }
    } else {
        auto sortedEntities = entities;
        std::sort(sortedEntities.begin() + start, sortedEntities.begin() + end, comparator);

        const int middle = start + span/2;

        node->_left = build(sortedEntities, start, middle, t0, t1);
        node->_right = build(sortedEntities, middle, end, t0, t1);
    }

    AABB lBbox, rBbox;

    if (!node->_left->getAABB(t0, t1, lBbox)|| !node->_right->getAABB(t0, t1, rBbox))
        throw "Error building Bvh";

    node->_bbox = AABB::surroundingBox(lBbox, rBbox);

    return node;
}
