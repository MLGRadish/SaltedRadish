#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void linkShader();

    GLuint getProgramId() {
        return _programId;
    }

private:
    void compileShader(const std::string& filePath, GLuint id);
    GLuint _programId;
    GLuint _vertexShaderId;
    GLuint _fragmentShaderId;
};
