#pragma once

#include "../common/geometry.h"

class Camera {
public:
    Camera(float aspectRatio) {
        _aspectRatio = aspectRatio;
        _focalLength = 1.0f;
        _viewportHeight = 2.0f;
        _viewportWidth = _aspectRatio * _viewportHeight;
        _position = Vec3(0.0f, 0.0f, 0.0f);
    }

    Ray viewportRay(float u, float v) const {
        const Vec3 vpH = Vec3(_viewportWidth, 0.0f, 0.0f);
        const Vec3 vpV = Vec3(0.0f, _viewportHeight, 0.0f);
        const Vec3 vpBL = _position - Vec3(_viewportWidth*0.5f, _viewportHeight*0.5f, _focalLength);

        return Ray(_position, Vec3::normalize(vpBL + u*vpH + v*vpV - _position));
    }

private:
    Vec3  _position;
    float _aspectRatio;
    float _focalLength;
    float _viewportHeight;
    float _viewportWidth;
};
