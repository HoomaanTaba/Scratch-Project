
#ifndef MOVEORDERS_MOVEORDERS_H
#define MOVEORDERS_MOVEORDERS_H

#endif //MOVEORDERS_MOVEORDERS_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
using namespace std;

Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
Uint32 WND_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
SDL_Window * m_window;
SDL_Renderer * m_renderer;

struct spirit {
    bool visible;
    double x;
    double y;
    double direction = 0;
};

spirit s;

int W = DM.w;
int H = MM.h;

double step = 1;

void move_n_steps (spirit&s, double n) {
    double rad = s.direction * M_PI / 180;
    double deltax, deltay;
    deltax = step*cos(rad);
    deltay = step*sin(rad);
    while (s.x != s.x + n*cos(rad) && s.y != s.y + n*sin(rad)) {
        s.x += deltax;
        s.y += deltay;
        if (s.x == 0 || s.x == W || s.y == 0 || s.y == H ) {
            s.direction *= -1;
        }
    }
}

void turn_angle_right (spirit&s , double angle) {
    s.direction += angle;
}

void turn_angle_left (spirit&s , double angle) {
    s.direction -= angle;
}

void go_to_randomposition (spirit&s ) {
    srand(time(NULL));
    double randX = rand() % W + 1;
    double randY = rand() % H + 1;
    s.x = randX;
    s.y = randY;
}

void go_to_x_and_y (spirit&s, double x, double y ) {
    s.x = x;
    s.y = y;
}

void change_x_by (spirit&s, double dx) {
    while (s.x != s.x + dx) {
        s.x += step;
        if (s.x == 0 || s.x == W) {
            s.direction *= -1;
        }
    }
}

void change_y_by (spirit&s, double dy) {
    while (s.y != s.y + dy) {
        s.y += step;
        if (s.y == 0 || s.y == H ) {
            s.direction *= -1;
        }
    }
}

void point_in_direction (spirit&s, double angle) {
    s.direction = angle;
}

void go_to_mouseposition (spirit&s ) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    s.x = mx;
    s.y = my;
    if (s.x == 0 || s.x == W || s.y == 0 || s.y == H ) {
        s.direction *= -1;
    }
}