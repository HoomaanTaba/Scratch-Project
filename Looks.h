//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_LOOKS_H
#define SCRATCH_LOOKS_H

#endif //SCRATCH_LOOKS_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include "UI_Objects.h"
using namespace std;


SideButton looksBtn = {
    1,
    "Looks",
    {153,102,255,255},
    {0,155,70,65},
    true
};

void show (Sprite& s) {
    s.visible = true;
}

void hide (Sprite& s) {
    s.visible = false;
}

void switch_costume_to (Sprite& s, int index) {
    if (index >= 0 && index < s.costume.size())
        s.currentCostume = index;
}

void next_costume (Sprite& s, int totalCostumes) {
    if (s.costume.size() == 0)
        return;

    s.currentCostume = (s.currentCostume + 1) % s.costume.size();
}

void change_size_by (Sprite& s, double amount) {
    s.size += amount;

    if (s.size > 540) {
        s.size = 540;
    }

    if (s.size < 5) {
        s.size = 5;
    }
}

void set_size (Sprite& s, double percentage) {
    s.size = percentage;

    if (s.size > 540) {
        s.size = 540;
    }

    if (s.size < 5) {
        s.size = 5;
    }
}

void say (Sprite& s, string text) {
    s.message = text;
    s.messageType = 1;

    s.messageDuration = 0;
}

void think (Sprite& s, string text) {
    s.message = text;
    s.messageType = 2;

    s.messageDuration = 0;
}

void say_for_seconds (Sprite& s, string text, int time) {
    s.message = text;
    s.messageType = 1;

    s.messageStartTime = SDL_GetTicks();
    s.messageDuration = time*1000;
}

void think_for_seconds (Sprite& s, string text, int time) {
    s.message = text;
    s.messageType = 2;

    s.messageStartTime = SDL_GetTicks();
    s.messageDuration = time*1000;
}

void update_message(Sprite& s) {
    if (s.messageDuration > 0) {
        Uint32 now = SDL_GetTicks();

        if (now - s.messageStartTime > s.messageDuration) {
            s.message = "";
            s.messageType = 0;
            s.messageDuration = 0;
        }
    }
}

void render_message (Sprite& s, SDL_Renderer* renderer, TTF_Font* font) {
    if (s.messageType == 0)
        return;

    SDL_Color textColor = {40, 40, 40};

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, s.message.c_str(), textColor);
    if (!textSurface)
        return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW = textSurface->w;
    int textH = textSurface->h;

    int padding = 20;

    int bubbleW = textW + padding;
    int bubbleH = textH + padding;

    int bubbleX = s.x - bubbleW/2;
    int bubbleY = s.y - 130;

    if (s.messageType == 1) {
        roundedBoxRGBA(
            renderer,
            bubbleX,
            bubbleY,
            bubbleW + bubbleX,
            bubbleH + bubbleY,
            18,
            255,255,255,255
            );

        roundedRectangleRGBA(
            renderer,
            bubbleX,
            bubbleY,
            bubbleW + bubbleX,
            bubbleH + bubbleY,
            18,
            180,180,180,255
            );

        Sint16 vx[3] = {
            (Sint16)(s.x - 10),
            (Sint16)(s.y + 10),
            (Sint16)(s.x)
        };

        Sint16 vy[3] = {
            (Sint16)(bubbleY + bubbleH),
            (Sint16)(bubbleY + bubbleH),
            (Sint16)(bubbleY + bubbleH + 20)
        };

        filledPolygonRGBA(renderer, vx, vy, 3, 255, 255, 255, 255);
        polygonRGBA(renderer, vx, vy, 3, 180, 180, 180, 255);
    }
    if (s.messageType == 2) {

        filledEllipseRGBA(
        renderer,
        s.x,
        bubbleY + bubbleH/2,
        bubbleW/2,
        bubbleH/2,
        255,255,255,255);

        ellipseRGBA(renderer,
            s.x,
            bubbleY + bubbleH/2,
            bubbleW/2,
            bubbleH/2,
            180, 180, 180, 255);

        filledCircleRGBA(renderer,
            s.x - 20,
            s.y - 50,
            7,
            255, 255, 255, 255);

        circleRGBA(renderer,
            s.x - 20,
            s.y - 50,
            7,
            180, 180, 180, 255);

        filledCircleRGBA(renderer,
            s.x - 10,
            s.y - 35,
            5,
            180, 180, 180, 255);

        circleRGBA(renderer,
            s.x - 10,
            s.y - 35,
            5,
            180, 180, 180, 255);
        }

    SDL_Rect textRect;
    textRect.w = textW;
    textRect.h = textH;
    textRect.x = s.x - textW/2;
    textRect.y = bubbleY + padding/2;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

