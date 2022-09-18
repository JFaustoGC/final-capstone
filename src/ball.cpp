#include "ball.h"


Ball::Ball() {
    body = {0, 0, 0, 0};
}

Ball::Ball(int size, int width, int height) {
    this->size = size;
    this->width = width;
    this->height = height;
    body.w = body.h = size;
}

void Ball::Serve() {
    body.x = (width / 2) - (size / 2);
    body.y = (height / 2) - (size / 2);
    (turn) ? direction = Direction::kLeft : direction = Direction::kRight;
    turn = (!turn);
}

void Ball::Update() {
    body.x += velX; 
    body.y += velY;
    if (body.y < 0 || body.y+size >= height) velY = -velY;
    Score();
}

void Ball::Score() {
    if (body.x <= 0) {
        Serve();
    }
    else if (body.x + body.w >= width) {
        Serve();
    }
}

void Ball::Collide(Direction side, Paddle &paddle) {
    double rel = (paddle.body.y+(paddle.body.h/2)) - (body.y+(size/2));
    double norm = rel/(paddle.body.h/2);
    double bounce = norm * (5*PI/12);    
    velY = speed * -sin(bounce);
    (side == Direction::kLeft) ? velX = speed * cos(bounce) : velX = -speed * cos(bounce);
}

