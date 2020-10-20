#include "stbHelper.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace StbHelper {

unsigned char* load(char const* szFileName, int* x, int* y, int* channels, int desiredChannels) {
    return stbi_load(szFileName, x, y, channels, desiredChannels);
}

int writePng(char const *szFileName, int x, int y, int comp, const void *data, int stride) {
    return stbi_write_png(szFileName, x, y, comp, data, stride);
}

}
