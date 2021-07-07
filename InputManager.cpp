#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::onKeyPess(unsigned int key) 
{
    _keyMap[key] = true;
}

void InputManager::onKeyRelease(unsigned int key)
{
    _keyMap[key] = false;
}

void InputManager::onMouseMove(glm::vec2 position)
{
    mousePosition = position;
}

bool InputManager::isKeyPressed(unsigned int key) 
{
    auto it = _keyMap.find(key);
    if (it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}
