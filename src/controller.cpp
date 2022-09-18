#include "controller.h"
#include <iostream>

void Controller::HandleInput(bool &running, Paddle &paddle) {
    SDL_Event e;
    const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;
        if (keyStates[SDL_SCANCODE_ESCAPE]) running = false;
        if (keyStates[SDL_SCANCODE_UP]) paddle.Move(Paddle::Direction::kUp);
        if (keyStates[SDL_SCANCODE_DOWN]) paddle.Move(Paddle::Direction::kDown);
    }
}
