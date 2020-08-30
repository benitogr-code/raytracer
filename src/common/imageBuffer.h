#include <vector>
#include "math.h"

// RGB image buffer

class ImageBuffer {
public:
    ImageBuffer(const int width, const int height)
        :_width(width)
        ,_height(height)
        ,_channels(3) // RGB
    {
        _data.resize(width * height * _channels);
    }

    void writePixel(int x, int y, const Color& color) {
        if (x < _width && y < _height) {
            const int stride = _width * _channels;
            const int pos = (y * stride) + (x * _channels);

            _data[pos] = (unsigned char)(255.0f * color.r);
            _data[pos+1] = (unsigned char)(255.0f * color.g);
            _data[pos+2] = (unsigned char)(255.0f * color.b);
        }
    }

    const int channels() const {
        return _channels;
    }

    const int width() const {
        return _width;
    }

    const int height() const {
        return _height;
    }

    const unsigned char* data() const {
        return _data.data();
    }

private:
    std::vector<unsigned char> _data;

    int _width;
    int _height;
    int _channels;
};
