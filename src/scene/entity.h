#pragma once

#include <memory>

#include "../common/hittable.h"

struct IEntity : public IHittable {
    virtual void setMaterial(IMaterialPtr material) = 0;
    virtual void setVelocity(const Vec3& velocity) = 0;
};

typedef std::shared_ptr<IEntity> IEntityPtr;
