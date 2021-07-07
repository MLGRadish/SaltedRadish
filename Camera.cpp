#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(): _viewMatrix(1.0f), _projectionMatrix(1.0f) {}

Camera::~Camera() {}

void Camera::init(float screenWidth, float screenHeight, GLSLProgram shader)
{
    _shader = shader;
    _projectionMatrix = glm::perspective(glm::radians(65.0f), screenWidth / screenHeight, 0.1f, 1000.0f);

    _viewMatrixIndex = glGetUniformLocation(_shader.getProgramId(), "view");
    _projectionMatrixIndex = glGetUniformLocation(_shader.getProgramId(), "proj");

    glUseProgram(_shader.getProgramId());
    glUniformMatrix4fv(_viewMatrixIndex, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(_projectionMatrixIndex, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
}

void Camera::update(glm::vec3 pos, glm::vec3 offset, float x, float y)
{
    glm::mat4 T = glm::mat4(1.0f);
    T = glm::rotate(T, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    T = glm::rotate(T, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    
    T = glm::translate(T, -pos-offset);

    _viewMatrix = T;
    glUniformMatrix4fv(_viewMatrixIndex, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
}
