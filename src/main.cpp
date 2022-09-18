#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "paddle.h"
#include "controller.h"
#include "ball.h"

#define WIDTH 720
#define HEIGHT 720

SDL_Renderer* renderer;
SDL_Window* window;
bool running;
int frameCount, timerFPS, lastFrame, fps;
Paddle l_paddle, r_paddle;
Controller controller;
Ball ball;

void render () {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);
    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/60)) {
     SDL_Delay((1000/60)-timerFPS);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &l_paddle.body);
    SDL_RenderFillRect(renderer, &r_paddle.body);
    SDL_RenderFillRect(renderer, &ball.body);

    SDL_RenderPresent(renderer);
}



int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;
    TTF_Init();

     running=true;
    static int lastTime = 0;

    l_paddle = Paddle(WIDTH, HEIGHT, Paddle::Side::kLeft);
    r_paddle = Paddle(WIDTH, HEIGHT, Paddle::Side::kRight);
    ball = Ball(16, WIDTH, HEIGHT);
    ball.Serve();
    

    while  (running) {
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }
        
        if (SDL_HasIntersection(&ball.body, &l_paddle.body)) ball.Collide(Ball::Direction::kLeft, l_paddle);
        if (SDL_HasIntersection(&ball.body, &r_paddle.body)) ball.Collide(Ball::Direction::kRight, r_paddle);
        controller.HandleInput(running, l_paddle);
        r_paddle.Follow(ball.body.y);
        ball.Update();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}