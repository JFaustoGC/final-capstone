#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>


class Paddle {

    public:

        enum class Side {kRight, kLeft};
        enum class Direction {kUp, kDown};

        Paddle();
        Paddle(int WIDTH, int HEIGHT, Paddle::Side side);
        void Move(Direction direction);
        void CheckBorder();
        void Follow(int y);
            

        SDL_Rect body;
        int speed{9};

};

#endif