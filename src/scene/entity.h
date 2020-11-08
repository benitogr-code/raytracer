#pragma once

#include <memory>

#include "../common/hittable.h"
#include "../common/matrix.h"

class Entity : public IHittable {
public:
    Entity(IMaterialPtr material)
    : _material(material)
    , _worldTM(Mat4x4::Identity())
    , _velocity(0.0f, 0.0f, 0.0f) {}

    void setWorldTM(const Mat4x4& m) {
        _worldTM = m;
        onWorldTMChanged(m);
    }

    void setVelocity(const Vec3& velocity) {
        _velocity = velocity;
    };

protected:
    virtual void onWorldTMChanged(const Mat4x4& m) {}

    const IMaterialPtr& material() const {
        return _material;
    }
    const Mat4x4& worldTM() const {
        return _worldTM;
    }
    const Vec3& velocity() const {
        return _velocity;
    }

private:
    IMaterialPtr _material;
    Mat4x4 _worldTM;
    Vec3 _velocity;
};

typedef std::shared_ptr<Entity> EntityPtr;
