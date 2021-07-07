#include "ImageLoader.h"
#include "GLTexture.h"
#include "picoPNG.h"
#include "err.h"
#include "IOManager.h"

GLTexture ImageLoader::loadPNG(std::string filePath)
{
    GLTexture texture = {};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;

    unsigned long width, height;

    if (IOManager::readToFileBuffer(filePath, in) == false) {
        fatalError("Failed to load cat images!");
    }

    int error = decodePNG(out, width, height, &in[0], in.size());
    if (error != 0) {
        fatalError("Failed to decode cat images!");
    }

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return texture;
}

GLTexture ImageLoader::loadCubemap(std::vector<std::string> faces) {
    GLTexture texture = {};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);

    unsigned long width, height;
    for (unsigned int i = 0; i < faces.size(); i++) {
        if (IOManager::readToFileBuffer(faces[i].c_str(), in) == false) {
            fatalError("Failed to load cat images! " + faces[i]);
        }

        int error = decodePNG(out, width, height, &in[0], in.size());
        if (error != 0) {
            fatalError("Failed to decode cat images!");
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    texture.width = width;
    texture.height = height;

    return texture;
}
