#ifndef BALL_H
#define BALL_H
#include "paddle.h"
#include <SDL2/SDL.h>

#define PI 3.14159265358979323846

class Ball {

    public:

    enum class Direction {kLeft, kRight};

    Ball();
    Ball(int size, int width, int height);
    void Serve();
    void Update();
    void Score();
    void Collide(Direction side, Paddle &paddle);
    void Bounce();

    SDL_Rect body;
    

    private:
        int speed{16};
        float velX{16};
        float velY;
        int size;
        int width;
        int height;
        bool turn{true};
        Direction direction{Direction::kLeft};
};

#endif