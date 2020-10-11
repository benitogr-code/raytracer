#pragma once

#include "../common/geometry.h"

class Camera {
public:
    Camera(float vFov, float aspectRatio, float aperture, float focusDistance, float shutterTime) {
        const float angle = Math::degreesToRadians(vFov);
        const float h = std::tanf(angle/2.0f);

        _aspectRatio = aspectRatio;
        _lensRadius = aperture / 2.0f;
        _focusDistance = focusDistance;
        _viewportHeight = 2.0f * h;
        _viewportWidth = _aspectRatio * _viewportHeight;
        _shutterTime = shutterTime;

        _position = Vec3(0.0f, 0.0f, 0.0f);
        _fwd = Vec3(0.0f, 0.0f, -1.0f);
        _right = Vec3(1.0f, 0.0f, 0.0f);
        _up = Vec3(0.0f, 1.0f, 0.0f);
    }

    void lookAt(const Vec3& position, const Vec3& target, const Vec3& up = Vec3(0.0f, 1.0f, 0.0f)) {
        const Vec3 lookAtDir = target - position;

        _position = position;
        _fwd = Vec3::normalize(lookAtDir);
        _right = Vec3::cross(_fwd, up);
        _up = Vec3::cross(_right, _fwd);
    }

    Ray viewportRay(float u, float v) const {
        const Vec3 vpH = _right * _viewportWidth * _focusDistance;
        const Vec3 vpV = _up * _viewportHeight * _focusDistance;
        const Vec3 vpBL = _position - vpH*0.5f - vpV*0.5f + _fwd*_focusDistance;

        const Vec3 r = _lensRadius * Vec3::randomUnitDisk();
        const Vec3 offset = _right * r.x + _up * r.y;
        const Vec3 origin = _position + offset;

        return Ray(origin, Vec3::normalize(vpBL + u*vpH + v*vpV - origin), Math::randf(0.0f, _shutterTime));
    }

private:
    Vec3  _position;
    Vec3  _fwd;
    Vec3  _right;
    Vec3  _up;

    float _aspectRatio;
    float _lensRadius;
    float _focusDistance;
    float _viewportHeight;
    float _viewportWidth;
    float _shutterTime;
};
