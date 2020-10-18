#pragma once

#include <memory>

#include "../common/hittable.h"

template<typename TGeom>
class Entity : public IHittable {
public:
    Entity(const TGeom& geometry, IMaterialPtr material)
        : _geometry(geometry)
        , _material(material)
        , _velocity(0.0f, 0.0f, 0.0f) {}

    void setVelocity(const Vec3& velocity) {
        _velocity = velocity;
    };

protected:
    const TGeom& geometry() const {
        return _geometry;
    }
    const IMaterialPtr& material() const {
        return _material;
    }
    const Vec3& velocity() const {
        return _velocity;
    }

private:
    TGeom _geometry;
    IMaterialPtr _material;
    Vec3 _velocity;
};
