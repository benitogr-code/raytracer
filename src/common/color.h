#pragma once

struct ColorRGB {
    ColorRGB() : _v{0.0f, 0.0f, 0.0f} {}
    ColorRGB(float r, float g, float b) : _v{r, g, b} {}

    ColorRGB& operator+=(const ColorRGB& c) {
        r += c.r;
        g += c.g;
        b += c.b;

        return *this;
    }
    ColorRGB& operator-=(const ColorRGB& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;

        return *this;
    }
    ColorRGB& operator*=(float f) {
        r *= f;
        g *= f;
        b *= f;

        return *this;
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

inline ColorRGB operator+(const ColorRGB& c1, const ColorRGB& c2) {
    return ColorRGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline ColorRGB operator-(const ColorRGB& c1, const ColorRGB& c2) {
    return ColorRGB(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline ColorRGB operator*(const ColorRGB &c, float f) {
    return ColorRGB(f*c.r, f*c.g, f*c.b);
}

inline ColorRGB operator*(float f, const ColorRGB &c) {
    return ColorRGB(f*c.r, f*c.g, f*c.b);
}

inline ColorRGB operator/(const ColorRGB &c, float f) {
    return ColorRGB(c.r/f, c.g/f, c.b/f);
}
