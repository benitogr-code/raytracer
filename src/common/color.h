#pragma once

struct ColorRGB {
    ColorRGB() : _v{0.0f, 0.0f, 0.0f} {}
    ColorRGB(float r, float g, float b) : _v{r, g, b} {}

    ColorRGB operator+(const ColorRGB& c) const {
        return ColorRGB(r + c.r, g + c.g, b + c.b);
    }
    ColorRGB& operator+=(const ColorRGB& c) {
        r += c.r;
        g += c.g;
        b += c.b;

        return *this;
    }
    ColorRGB operator-(const ColorRGB& c) const {
        return ColorRGB(r - c.r, g - c.g, b - c.b);
    }
    ColorRGB& operator-=(const ColorRGB& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;

        return *this;
    }

    ColorRGB operator*(float f) const {
        return ColorRGB(r * f, g * f, b * f);
    }
    ColorRGB& operator*=(float f) {
        r *= f;
        g *= f;
        b *= f;

        return *this;
    }
    ColorRGB operator/(float f) const {
        return ColorRGB(r/f, g/f, b/f);
    }
    ColorRGB& operator/=(float f) {
        r /= f;
        g /= f;
        b /= f;

        return *this;
    }

    union {
        struct { float r, g, b; };
        float _v[3];
    };
};
