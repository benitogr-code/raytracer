#pragma once

#include "../common/geometry.h"

class Camera {
public:
    Camera(float vFov, float aspectRatio) {
        const float angle = Math::degreesToRadians(vFov);
        const float h = std::tanf(angle/2.0f);

        _aspectRatio = aspectRatio;
        _viewportHeight = 2.0f * h;
        _viewportWidth = _aspectRatio * _viewportHeight;

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
        const Vec3 vpH = _right * _viewportWidth;
        const Vec3 vpV = _up * _viewportHeight;
        const Vec3 vpBL = _position - vpH*0.5f - vpV*0.5f + _fwd;

        return Ray(_position, Vec3::normalize(vpBL + u*vpH + v*vpV - _position));
    }

private:
    Vec3  _position;
    Vec3  _fwd;
    Vec3  _right;
    Vec3  _up;
    float _aspectRatio;
    float _viewportHeight;
    float _viewportWidth;
};
