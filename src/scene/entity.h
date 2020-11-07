#pragma once

#include <memory>

#include "../common/hittable.h"

class Entity : public IHittable {
public:
    Entity(IMaterialPtr material)
        : _material(material)
        , _velocity(0.0f, 0.0f, 0.0f) {}

    void setVelocity(const Vec3& velocity) {
        _velocity = velocity;
    };

protected:
    const IMaterialPtr& material() const {
        return _material;
    }
    const Vec3& velocity() const {
        return _velocity;
    }

private:
    IMaterialPtr _material;
    Vec3 _velocity;
};

typedef std::shared_ptr<Entity> EntityPtr;
