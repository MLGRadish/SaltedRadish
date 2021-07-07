#pragma once
#include "GLTexture.h"

#include <string>
#include <vector>

class ImageLoader {
public:
	static GLTexture loadPNG(std::string filePath);
    static GLTexture loadCubemap(std::vector<std::string> faces);
};
