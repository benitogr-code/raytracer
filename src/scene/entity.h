#pragma once

#include <memory>

#include "../common/hittable.h"
#include "../common/matrix.h"

class Entity : public IHittable {
public:
    Entity(IMaterialPtr material)
    : _material(material)
    , _worldTM(Mat4x4::Identity()) {}

    Entity(const Vec3& pos, IMaterialPtr material)
    : _material(material)
    , _worldTM(Mat4x4::Translation(pos)) {}

    void setWorldTM(const Mat4x4& m) {
        _worldTM = m;
        onWorldTMChanged(m);
    }

protected:
    virtual void onWorldTMChanged(const Mat4x4& m) {}

protected:
    IMaterialPtr _material;
    Mat4x4 _worldTM;
};

typedef std::shared_ptr<Entity> EntityPtr;
