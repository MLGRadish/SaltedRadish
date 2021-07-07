#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

class Window {
public:
    Window();
    ~Window();

    int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

    int getScreenWidth() { return _screenWidth; };
    int getScreenHeight() { return _screenHeight; };

    void swapBuffer();

    SDL_Window* getWindow() { return _sdlWindow; };
    SDL_GLContext* getConext() { return &_glContext; };

private:
    SDL_Window* _sdlWindow;
    SDL_GLContext _glContext;
    int _screenWidth, _screenHeight;
};
