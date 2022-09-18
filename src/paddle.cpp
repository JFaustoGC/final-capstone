#include "paddle.h"

Paddle::Paddle() {
    body = {0, 0, 0, 0};
}

Paddle::Paddle(int width, int height, Paddle::Side side) {
    body.w = width / 60;
    body.h = height / 4;
    body.y = (height / 2) - (body.h / 2);
    if (side == Paddle::Side::kLeft) body.x = width / 22 ;
    else body.x = width - body.w - body.x;
}

void Paddle::Move(Paddle::Direction direction) {
    (direction == Paddle::Direction::kDown) ? body.y += speed : body.y -= speed;
    CheckBorder();
}

void Paddle::CheckBorder() {
    if (body.y < 0) body.y = 0;
    if (body.y > body.h * 5) body.y = body.h * 3;
}

void Paddle::Follow(int y) {
    if (y > body.y+(body.h/2)) Move(Direction::kDown);
    if (y < body.y+(body.h/2)) Move(Direction::kUp);
    
}