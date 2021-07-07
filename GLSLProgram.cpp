#include "GLSLProgram.h"
#include "err.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programId(0), _vertexShaderId(0), _fragmentShaderId(0) {}

GLSLProgram::~GLSLProgram() {}

void GLSLProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderId == 0) {
        fatalError("Failed to create vertex shader");
    }

    _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderId == 0) {
        fatalError("Failed to create fragment shader");
    }

    compileShader(vertexShaderPath, _vertexShaderId);
    compileShader(fragmentShaderPath, _fragmentShaderId);
}

void GLSLProgram::linkShader()
{
    glAttachShader(_programId, _vertexShaderId);
    glAttachShader(_programId, _fragmentShaderId);
    glLinkProgram(_programId);

    GLint isLinked = 0;
    glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(_programId);
        glDeleteShader(_vertexShaderId);
        glDeleteShader(_fragmentShaderId);

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Failed to link shader");
    }
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
{
    _programId = glCreateProgram();
    std::ifstream vertexFile(filePath);

    if (vertexFile.fail()) {
        fatalError("Error in shader: " + filePath);
    }
    std::string fileContents = "";
    std::string line;

    while (std::getline(vertexFile, line)) {
        fileContents += line + "\n";
    }

    vertexFile.close();

    const char* contentPtr = fileContents.c_str();

    glShaderSource(id, 1, &contentPtr, nullptr);
    glCompileShader(id);

    GLint sucess = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
    
    if (sucess == GL_FALSE) {
        GLint maxLenght = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLenght);

        std::vector<char> errorLog(maxLenght);
        glGetShaderInfoLog(id, maxLenght, &maxLenght, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Problem with shader");
    }
}
