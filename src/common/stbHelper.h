#pragma once

namespace StbHelper {

unsigned char* load(char const* szFileName, int* x, int* y, int* channels, int desiredChannels);
int writePng(char const* szFileName, int x, int y, int comp, const void* data, int stride);

}
