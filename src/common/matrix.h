#pragma once

#include "vector.h"

// Colum-major 4x4 Matrix
// In memory represented as flatten array:
// m00 m01 m02 m03 - Column 0
// m10 m11 m12 m13 - Column 1
// m20 m21 m22 m23 - Column 2
// m30 m31 m32 m33 - Column 3

struct Mat4x4 {
    Mat4x4() {
    }
    Mat4x4(float c00, float c01, float c02, float c03, float c10, float c11, float c12, float c13,
        float c20, float c21, float c22, float c23, float c30, float c31, float c32, float c33) {
        _m[0] = c00, _m[1] = c01, _m[2] = c02, _m[3] = c03;
        _m[4] = c10, _m[5] = c11, _m[6] = c12, _m[7] = c13;
        _m[8] = c20, _m[9] = c21, _m[10] = c22, _m[11] = c23;
        _m[12] = c30, _m[13] = c31, _m[14] = c32, _m[15] = c33;
    }

    Vec4   operator*(const Vec4 &rhs) const {
        const float x = m00 * rhs.x + m10 * rhs.y + m20 * rhs.z + m30 * rhs.w;
        const float y = m01 * rhs.x + m11 * rhs.y + m21 * rhs.z + m31 * rhs.w;
        const float z = m02 * rhs.x + m12 * rhs.y + m22 * rhs.z + m32 * rhs.w;
        const float w = m03 * rhs.x + m13 * rhs.y + m23 * rhs.z + m33 * rhs.w;

        return Vec4(x, y, z, w);
    }

    Mat4x4 operator*(const Mat4x4 &rhs) const {
        Mat4x4 result = Mat4x4::Zero();
        int index = 0;

        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
            float sum = 0.0f;

            for (int i = 0; i < 4; i++) {
                sum += rhs._m[i + col * 4] * _m[row + i * 4];
            }

            result._m[index] = sum;
            index++;
            }
        }

        return result;
    }

    Mat4x4& operator=(const Mat4x4 &rhs) {
        for (int i = 0; i < 16; i++) {
            _m[i] = rhs._m[i];
        }

        return *this;
    }

    void   setTranslation(const Vec3& t) {
        m30 = t.x; m31 = t.y; m32 = t.z;
    }

    Vec3   getTranslation() const {
        return Vec3(m30, m31, m32);
    }

    static Mat4x4 Zero() {
        return Mat4x4(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f);
    }

    static Mat4x4 Identity() {
        return Mat4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Mat4x4 Translation(const Vec3& t) {
        return Mat4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            t.x, t.y, t.z, 1.0f);
    }

    static float Determinant(const Mat4x4& m) {
        return
            m.m30 * m.m21 * m.m12 * m.m03 -
            m.m20 * m.m31 * m.m12 * m.m03 -
            m.m30 * m.m11 * m.m22 * m.m03 +
            m.m10 * m.m31 * m.m22 * m.m03 +
            m.m20 * m.m11 * m.m32 * m.m03 -
            m.m10 * m.m21 * m.m32 * m.m03 -
            m.m30 * m.m21 * m.m02 * m.m13 +
            m.m20 * m.m31 * m.m02 * m.m13 +
            m.m30 * m.m01 * m.m22 * m.m13 -
            m.m00 * m.m31 * m.m22 * m.m13 -
            m.m20 * m.m01 * m.m32 * m.m13 +
            m.m00 * m.m21 * m.m32 * m.m13 +
            m.m30 * m.m11 * m.m02 * m.m23 -
            m.m10 * m.m31 * m.m02 * m.m23 -
            m.m30 * m.m01 * m.m12 * m.m23 +
            m.m00 * m.m31 * m.m12 * m.m23 +
            m.m10 * m.m01 * m.m32 * m.m23 -
            m.m00 * m.m11 * m.m32 * m.m23 -
            m.m20 * m.m11 * m.m02 * m.m33 +
            m.m10 * m.m21 * m.m02 * m.m33 +
            m.m20 * m.m01 * m.m12 * m.m33 -
            m.m00 * m.m21 * m.m12 * m.m33 -
            m.m10 * m.m01 * m.m22 * m.m33 +
            m.m00 * m.m11 * m.m22 * m.m33;
    }

    static Mat4x4 Inverse(const Mat4x4& m) {
        const float det = Mat4x4::Determinant(m);
        if (det == 0.0f) {
            return m;
        }

        const float invDet = 1.0f / det;

        return Mat4x4(
            invDet * ( m.m21 * m.m32 * m.m13 - m.m31 * m.m22 * m.m13 +
                        m.m31 * m.m12 * m.m23 - m.m11 * m.m32 * m.m23 -
                        m.m21 * m.m12 * m.m33 + m.m11 * m.m22 * m.m33 ),
            invDet * ( m.m31 * m.m22 * m.m03 - m.m21 * m.m32 * m.m03 -
                        m.m31 * m.m02 * m.m23 + m.m01 * m.m32 * m.m23 +
                        m.m21 * m.m02 * m.m33 - m.m01 * m.m22 * m.m33 ),
            invDet * ( m.m11 * m.m32 * m.m03 - m.m31 * m.m12 * m.m03 +
                        m.m31 * m.m02 * m.m13 - m.m01 * m.m32 * m.m13 -
                        m.m11 * m.m02 * m.m33 + m.m01 * m.m12 * m.m33 ),
            invDet * ( m.m21 * m.m12 * m.m03 - m.m11 * m.m22 * m.m03 -
                        m.m21 * m.m02 * m.m13 + m.m01 * m.m22 * m.m13 +
                        m.m11 * m.m02 * m.m23 - m.m01 * m.m12 * m.m23 ),
            invDet * ( m.m30 * m.m22 * m.m13 - m.m20 * m.m32 * m.m13 -
                        m.m30 * m.m12 * m.m23 + m.m10 * m.m32 * m.m23 +
                        m.m20 * m.m12 * m.m33 - m.m10 * m.m22 * m.m33 ),
            invDet * ( m.m20 * m.m32 * m.m03 - m.m30 * m.m22 * m.m03 +
                        m.m30 * m.m02 * m.m23 - m.m00 * m.m32 * m.m23 -
                        m.m20 * m.m02 * m.m33 + m.m00 * m.m22 * m.m33 ),
            invDet * ( m.m30 * m.m12 * m.m03 - m.m10 * m.m32 * m.m03 -
                        m.m30 * m.m02 * m.m13 + m.m00 * m.m32 * m.m13 +
                        m.m10 * m.m02 * m.m33 - m.m00 * m.m12 * m.m33 ),
            invDet * ( m.m10 * m.m22 * m.m03 - m.m20 * m.m12 * m.m03 +
                        m.m20 * m.m02 * m.m13 - m.m00 * m.m22 * m.m13 -
                        m.m10 * m.m02 * m.m23 + m.m00 * m.m12 * m.m23 ),
            invDet * ( m.m20 * m.m31 * m.m13 - m.m30 * m.m21 * m.m13 +
                        m.m30 * m.m11 * m.m23 - m.m10 * m.m31 * m.m23 -
                        m.m20 * m.m11 * m.m33 + m.m10 * m.m21 * m.m33 ),
            invDet * ( m.m30 * m.m21 * m.m03 - m.m20 * m.m31 * m.m03 -
                        m.m30 * m.m01 * m.m23 + m.m00 * m.m31 * m.m23 +
                        m.m20 * m.m01 * m.m33 - m.m00 * m.m21 * m.m33 ),
            invDet * ( m.m10 * m.m31 * m.m03 - m.m30 * m.m11 * m.m03 +
                        m.m30 * m.m01 * m.m13 - m.m00 * m.m31 * m.m13 -
                        m.m10 * m.m01 * m.m33 + m.m00 * m.m11 * m.m33 ),
            invDet * ( m.m20 * m.m11 * m.m03 - m.m10 * m.m21 * m.m03 -
                        m.m20 * m.m01 * m.m13 + m.m00 * m.m21 * m.m13 +
                        m.m10 * m.m01 * m.m23 - m.m00 * m.m11 * m.m23 ),
            invDet * ( m.m30 * m.m21 * m.m12 - m.m20 * m.m31 * m.m12 -
                        m.m30 * m.m11 * m.m22 + m.m10 * m.m31 * m.m22 +
                        m.m20 * m.m11 * m.m32 - m.m10 * m.m21 * m.m32 ),
            invDet * ( m.m20 * m.m31 * m.m02 - m.m30 * m.m21 * m.m02 +
                        m.m30 * m.m01 * m.m22 - m.m00 * m.m31 * m.m22 -
                        m.m20 * m.m01 * m.m32 + m.m00 * m.m21 * m.m32 ),
            invDet * ( m.m30 * m.m11 * m.m02 - m.m10 * m.m31 * m.m02 -
                        m.m30 * m.m01 * m.m12 + m.m00 * m.m31 * m.m12 +
                        m.m10 * m.m01 * m.m32 - m.m00 * m.m11 * m.m32 ),
            invDet * ( m.m10 * m.m21 * m.m02 - m.m20 * m.m11 * m.m02 +
                        m.m20 * m.m01 * m.m12 - m.m00 * m.m21 * m.m12 -
                        m.m10 * m.m01 * m.m22 + m.m00 * m.m11 * m.m22 ) );
    }

    static Mat4x4 Transpose(const Mat4x4& m) {
        return Mat4x4(
            m.m00, m.m10, m.m20, m.m30,
            m.m01, m.m11, m.m21, m.m31,
            m.m02, m.m12, m.m22, m.m32,
            m.m03, m.m13, m.m23, m.m33);
    }

    static Mat4x4 Tranlate(const Mat4x4& m, const Vec3& t) {
          return Mat4x4::Translation(t) * m;
    }

    static Mat4x4 RotateX(const Mat4x4& m, float degrees) {
        const float rad = Math::degreesToRadians(degrees);
        const float cosine = cosf(rad);
        const float sine = sinf(rad);

        Mat4x4 rotationMtx = Mat4x4::Identity();
        rotationMtx.m11 = cosine;
        rotationMtx.m12 = sine;
        rotationMtx.m21 = -sine;
        rotationMtx.m22 = cosine;

        return rotationMtx * m;
    }

    static Mat4x4 RotateY(const Mat4x4& m, float degrees) {
        const float rad = Math::degreesToRadians(degrees);
        const float cosine = cosf(rad);
        const float sine = sinf(rad);

        Mat4x4 rotationMtx = Mat4x4::Identity();
        rotationMtx.m00 = cosine;
        rotationMtx.m02 = -sine;
        rotationMtx.m20 = sine;
        rotationMtx.m22 = cosine;

        return rotationMtx * m;
    }

    static Mat4x4 RotateZ(const Mat4x4& m, float degrees) {
        const float rad = Math::degreesToRadians(degrees);
        const float cosine = cosf(rad);
        const float sine = sinf(rad);

        Mat4x4 rotationMtx = Mat4x4::Identity();
        rotationMtx.m00 = cosine;
        rotationMtx.m01 = sine;
        rotationMtx.m10 = -sine;
        rotationMtx.m11 = cosine;

        return rotationMtx * m;
    }

    static Mat4x4 Scale(float scale) {
        Mat4x4 ms = Mat4x4::Identity();
        ms.m00 = scale;
        ms.m11 = scale;
        ms.m22 = scale;

        return ms;
    }

    static Mat4x4 Scale(const Mat4x4& m, float scale) {
        return Mat4x4::Scale(scale) * m;
    }

    union {
        struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
        };
        float _m[16];
    };
};
