#include <iostream>
#include "SDL.h"

#define WIDHT 640
#define HEIGHT 640
#define SIZE 16
#define BALL_SPEED 16
#define SPEED 9
#define PI 3.14159265358979323846

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Color color;
bool running;
int frameCount,timerFPS, lastFrame, fps;

SDL_Rect l_paddle, r_paddle, ball;
float velX, velY;
int l_s, r_s;
bool turn;

void serve() {
  r_paddle.y = l_paddle.y = (HEIGHT/2)-(l_paddle.h/2);
  if (turn) {
    ball.x = l_paddle.x + (l_paddle.w * 4);
    velX = BALL_SPEED/2;
  }
  else {
    ball.x = r_paddle.x - (l_paddle.w * 4);
    velX = -BALL_SPEED/2;
  }
  ball.y = HEIGHT/2 - (SIZE/2);
  turn = !turn;
}

void update() {
  if(SDL_HasIntersection(&ball, &r_paddle)) {
    double rel = (r_paddle.y+(r_paddle.h/2))-(ball.y+(SIZE/2));
    double norm = rel/(r_paddle.h/2);
    double bounce = norm*(5*PI/12);
    velX = -BALL_SPEED * cos(bounce);
    velY = BALL_SPEED * -sin(bounce);
  }
  if(SDL_HasIntersection(&ball, &l_paddle)) {
    double rel = (l_paddle.y+(l_paddle.h/2))-(ball.y+(SIZE/2));
    double norm = rel/(l_paddle.h/2);
    double bounce = norm*(5*PI/12);
    velX = BALL_SPEED * cos(bounce);
    velY = BALL_SPEED * -sin(bounce);
  }
  if(ball.y > r_paddle.y+(r_paddle.h/2)) r_paddle.y += SPEED;
  if(ball.y < r_paddle.y+(r_paddle.h/2)) r_paddle.y -= SPEED;
  if(ball.x <= 0) serve();
  if(ball.x+SIZE>=WIDHT) serve();
  if(ball.y <= 0 || ball.y+SIZE>=WIDHT) velY = -velY;
  ball.x += velX;
  ball.y += velY;
  if(l_paddle.y < 0) l_paddle.y = 0;
  if(l_paddle.y+ l_paddle.h>HEIGHT) l_paddle.y = HEIGHT - r_paddle.h;
  if(r_paddle.y < 0) r_paddle.y = 0;
  if(r_paddle.y+ r_paddle.h>HEIGHT) r_paddle.y = HEIGHT - r_paddle.h;
  
};

void input() {
  SDL_Event e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  while(SDL_PollEvent(&e)) if(e.type == SDL_QUIT) running = false;
  if(keystates[SDL_SCANCODE_ESCAPE]) running = false;
  if(keystates[SDL_SCANCODE_UP]) l_paddle.y -= SPEED;
  if(keystates[SDL_SCANCODE_DOWN]) l_paddle.y += SPEED;
};

void render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
  SDL_RenderClear(renderer);

  frameCount++;
  timerFPS = SDL_GetTicks() - lastFrame;
  if (timerFPS < (1000/60)) {
    SDL_Delay((1000/60) - timerFPS);
  }

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer, &l_paddle);
  SDL_RenderFillRect(renderer, &r_paddle);
  SDL_RenderFillRect(renderer, &ball);
  SDL_RenderPresent(renderer);
}

int main() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
  if(SDL_CreateWindowAndRenderer(WIDHT, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
  
  running = true;
  static int lastTime = 0;

  color.r = color.g = color.b = 255;
  l_paddle.x = 32, l_paddle.h = HEIGHT/4;
  l_paddle.y = (HEIGHT/2)-(l_paddle.h/2);
  l_paddle.w = 12;
  r_paddle = l_paddle;
  r_paddle.x = WIDHT - r_paddle.w - 32;
  ball.w = ball.h = SIZE;

  serve();

  while (running) {
    lastFrame = SDL_GetTicks();
    if (lastFrame >= (lastTime+1000)) {
      lastTime = lastFrame;
      fps = frameCount;
      frameCount = 0;
    }

    update();
    input();
    render();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}