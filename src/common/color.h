#pragma once

#include "math.h"

struct Color {
    Color() : _v{0.0f, 0.0f, 0.0f} {}
    Color(float r, float g, float b) : _v{r, g, b} {}

    Color& operator+=(const Color& c) {
        r += c.r;
        g += c.g;
        b += c.b;

        return *this;
    }
    Color& operator-=(const Color& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;

        return *this;
    }
    Color& operator*=(float f) {
        r *= f;
        g *= f;
        b *= f;

        return *this;
    }
    Color& operator/=(float f) {
        r /= f;
        g /= f;
        b /= f;

        return *this;
    }

    static Color random() {
        return Color(Math::randf(), Math::randf(), Math::randf());
    }

    static Color random(float min, float max) {
        return Color(
            Math::randf(min, max),
            Math::randf(min, max),
            Math::randf(min, max)
        );
    }

    union {
        struct { float r, g, b; };
        float _v[3];
    };
};

inline Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline Color operator-(const Color& c1, const Color& c2) {
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline Color operator*(const Color &c1, const Color& c2) {
    return Color(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
}

inline Color operator*(const Color &c, float f) {
    return Color(f*c.r, f*c.g, f*c.b);
}

inline Color operator*(float f, const Color &c) {
    return Color(f*c.r, f*c.g, f*c.b);
}

inline Color operator/(const Color &c, float f) {
    return Color(c.r/f, c.g/f, c.b/f);
}
