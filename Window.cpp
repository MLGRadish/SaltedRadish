#include "Window.h"
#include "err.h"

Window::Window(): _sdlWindow(nullptr), _screenWidth(1024), _screenHeight(768) {}

Window::~Window() {}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) 
{
    Uint32 flags = SDL_WINDOW_OPENGL;

    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }

    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }

    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
    if (_sdlWindow == nullptr) {
        fatalError("Failed to create SDL window");
    }

    _glContext = SDL_GL_CreateContext(_sdlWindow);
    if (_glContext == nullptr) {
        fatalError("Failed to create glContext");
    }

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Failed to initialise glew");
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL Version %s\n", version);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    SDL_GL_SetSwapInterval(0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    return 0;
}

void Window::swapBuffer() 
{
    SDL_GL_SwapWindow(_sdlWindow);
}
