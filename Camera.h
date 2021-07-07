#pragma once
#include "GLSLProgram.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class Camera {
public:
    Camera();
    ~Camera();

    void init(float screenWidth, float screenHeight, GLSLProgram shader);
    void update(glm::vec3 pos, glm::vec3 offset, float x, float y);

    glm::mat4 getViewMatrix() {
        return _viewMatrix;
    }

    glm::mat4 getProjectionMatrix() {
        return _projectionMatrix;
    }

private:
    GLint _viewMatrixIndex;
    GLint _projectionMatrixIndex;
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;
    GLSLProgram _shader;
};
