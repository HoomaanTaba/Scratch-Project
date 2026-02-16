//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_UI_OBJECTS_H
#define SCRATCH_UI_OBJECTS_H

// Scratch Project - UI Objects


#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfx.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "string"
#include "vector"
using namespace std;

// Creating Scratch Character

struct DisplayMode {
    int w;
    int h;
};

DisplayMode DM = {1920, 1080};
inline int W = DM.w;
inline int H = DM.h;

struct Sprite {
    SDL_Texture* texture;
    SDL_Rect rect;
    bool dragging;
    bool visible;
    double x;
    double y;
    double direction = 0;

    vector <SDL_Texture*> costume;
    int currentCostume = 0;

    string message;
    int messageType;
    // 0 = Noun
    // 1 = Say
    // 2 = Think

    Uint32 messageStartTime = 0;
    Uint32 messageDuration = 0;

    double size = 100;
    double colorEffect = 0;
    int layer = 0;
};

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& path) {
    SDL_Surface* surf = IMG_Load(path.c_str());
    if (!surf) return nullptr;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}
void drawCat(SDL_Renderer* renderer, Sprite& s) {
    if (s.texture)
        SDL_RenderCopy(renderer, s.texture, nullptr, &s.rect);
}
bool mouseOnSprite(int mx, int my, Sprite& s) {
    return mx >= s.rect.x && mx <= s.rect.x + s.rect.w &&
           my >= s.rect.y && my <= s.rect.y + s.rect.h;
}
void handleSpriteEvent(Sprite& s, SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN &&
        e.button.button == SDL_BUTTON_LEFT) {

        int mx = e.button.x;
        int my = e.button.y;

        if (mouseOnSprite(mx, my, s)) {
            s.dragging = true;

            // فاصله‌ی کلیک تا گوشه‌ی Sprite
            s.x = mx - s.rect.x;
            s.y = my - s.rect.y;
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP &&
        e.button.button == SDL_BUTTON_LEFT) {

        s.dragging = false;
    }

    if (e.type == SDL_MOUSEMOTION && s.dragging) {
        s.rect.x = e.motion.x - s.x;
        s.rect.y = e.motion.y - s.y;
    }
}


// Creating Blue title bar
void drawTitleBar(SDL_Renderer* r, SDL_Window* w) {
    int winW, winH;
    SDL_GetWindowSize(w, &winW, &winH);

    SDL_Rect bar = {0, 0, winW, 50};
    SDL_SetRenderDrawColor(r, 77, 151, 255, 255);
    SDL_RenderFillRect(r, &bar);
}

// function to draw text on buttons, tabs, ...
void drawTextCentered(SDL_Renderer* r, TTF_Font* font,
                      const string& text, SDL_Rect rect,
                      SDL_Color color) {

    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(r, surf);

    int tw, th;
    SDL_QueryTexture(tex, nullptr, nullptr, &tw, &th);

    SDL_Rect dst = {
            rect.x + (rect.w - tw) / 2,
            rect.y + (rect.h - th) / 2,
            tw, th
    };

    SDL_RenderCopy(r, tex, nullptr, &dst);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

// function to check if mouse is in a special area or not
bool isInside(int x, int y, SDL_Rect r) {
    return x >= r.x && x <= r.x + r.w &&
           y >= r.y && y <= r.y + r.h;
}

// Creating tabs
struct Tab {
    SDL_Rect rect;
    string text;
    bool active;
    SDL_Color color;
};
void drawTab(SDL_Renderer* renderer, TTF_Font* font, Tab& tab) {
    // color of background
    if (tab.active)
        SDL_SetRenderDrawColor(renderer, 200, 220, 255, 255);
    else
        SDL_SetRenderDrawColor(renderer, tab.color.r, tab.color.g, tab.color.b, 255);

    SDL_RenderFillRect(renderer, &tab.rect);

    // cadre
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &tab.rect);

    //text color of active tab
    SDL_Color textColor = tab.active ?
                          SDL_Color{30, 30, 30} :
                          SDL_Color{100, 100, 100};

    drawTextCentered(renderer, font, tab.text, tab.rect, textColor);

    // Underline and change the color of active tab
    if (tab.active) {
        SDL_Rect underline = {tab.rect.x, tab.rect.y + tab.rect.h - 3, tab.rect.w, 3};
        SDL_SetRenderDrawColor(renderer, 77, 151, 255, 255);
        SDL_RenderFillRect(renderer, &underline);
    }
}
Tab CodeTab = {{0, 50, 70, 40}, "Code", false, {217, 227, 242}};
Tab CustomTab = {{70, 50, 70, 40}, "Costumes", false, {217, 227, 242}};
Tab SoundTab = {{140, 50, 70, 40}, "Sounds", false, {217, 227, 242}};

// making File and Edit tabs
Tab File = {{150, 7, 50, 40}, "File", false, {217, 227, 242}};
Tab Edit = {{200, 7, 50, 40}, "Edit", false, {217, 227, 242}};


void drawStaticImage(SDL_Renderer* renderer, SDL_Texture* tex, int x, int y, int w, int h) {
    if(tex) {
        SDL_Rect destRect = {x, y, w, h};
        SDL_RenderCopy(renderer, tex, nullptr, &destRect);
    }
}

// drawing side_buttons in Code menu
struct SideButton {
    int id;
    string label;
    SDL_Color color;
    SDL_Rect area;
    bool active;
};
void drawSideButton(SDL_Renderer* r, TTF_Font* font, SideButton& btn) {
    if(btn.active) {
        SDL_SetRenderDrawColor(r, 230, 240, 255, 255);
        SDL_RenderFillRect(r, &btn.area);
    }

    // calculating the center of circle
    int centerX = btn.area.x + btn.area.w/2;
    int centerY = btn.area.y+25;
    int radius = 13;

    // drawing colored circle
    filledCircleRGBA(r,centerX,centerY,radius,btn.color.r,btn.color.g,btn.color.b,255);
    aacircleRGBA(r, centerX, centerY, radius, btn.color.r, btn.color.g, btn.color.b, 255);
    SDL_Color textColor = {100, 100, 100, 255};
    SDL_Rect textContainer = {btn.area.x, btn.area.y+40, btn.area.w, 20};

    drawTextCentered(r,font,btn.label,textContainer , textColor);
}

// Define blocks struct
struct DraggableBlock {
    SDL_Texture* texture;
    SDL_Rect rect;
    bool dragging = false;
    int offsetX = 0, offsetY = 0;
    // Checking that is it a head block or not
    bool isHat;
    int parentID = -1;
    int id;
    // DropDown Support
    bool hasDropdown = false;
    vector<string> dropdownOptions;
    int selectedOption = 0;
    bool dropdownOpen = false;
    SDL_Rect dropdownRect;
};


extern vector<DraggableBlock> workspaceBlocks;

extern vector<DraggableBlock> EventMenuBlocks;
extern vector<DraggableBlock> SoundMenuBlocks;


#endif //SCRATCH_UI_OBJECTS_H