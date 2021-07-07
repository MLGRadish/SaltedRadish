#include "Timing.h"

#include <SDL2/SDL.h>

FpsLimiter::FpsLimiter() {}

void FpsLimiter::init(float maxFPS)
{
    setMaxFPS(maxFPS);
}

void FpsLimiter::setMaxFPS(float maxFPS) 
{
    _maxFPS = maxFPS;
}

void FpsLimiter::begin()
{
    _startTics = SDL_GetTicks();
}

void FpsLimiter::_calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static int currentFrame = 0;
    static float frameTimes[NUM_SAMPLES];
    static float prevTics = SDL_GetTicks();
    float currentTics;
    currentTics = SDL_GetTicks();

    _frameTime = currentTics - prevTics;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    prevTics = currentTics;

    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;

    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }
}

float FpsLimiter::end()
{
    _calculateFPS();

    float frameTicks = SDL_GetTicks() - _startTics;
    
    if (1000.0f / _maxFPS > frameTicks) {
        SDL_Delay(1000.0f / _maxFPS - frameTicks);
    }

    return _fps;
}
