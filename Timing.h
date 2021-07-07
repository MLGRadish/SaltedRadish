#pragma once

class FpsLimiter {
public:
    FpsLimiter();

    void init(float maxFPS);
    void setMaxFPS(float maxFPS);
    void begin();
    float end();

private:
    float _fps;
    float _maxFPS;
    float _frameTime;

    void _calculateFPS();

    unsigned int _startTics;
};
