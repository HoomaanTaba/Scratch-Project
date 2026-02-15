#include "iostream"
#include "cmath"
#include "UI_Objects.h"
#include "Motion.h"
#include "Looks.h"
#include "Sound.h"
#include "Events.h"
#include "Control.h"
#include "Sensing.h"
#include "Operators.h"
#include "Variables.h"

int main(int argc, char* argv[]) {
    // SDL Initialize
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // Window Icon Initilize
    IMG_Init(IMG_INIT_PNG);

    // Window making
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_CreateWindowAndRenderer(
            1024, 610, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE,
            &m_window, &m_renderer);

    SDL_RaiseWindow(m_window);

    //Setting icon to the window
    SDL_Surface* icon = IMG_Load("icon.png");
    if(!icon) {
        cout << "Icon load error: " << IMG_GetError() << endl;
    }
    else {
        SDL_SetWindowIcon(m_window, icon);
        SDL_FreeSurface(icon);
    }

    // Initialize font
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("arial.ttf", 14);
    if(!font) {
        cout << "Font load error: " << TTF_GetError() << endl;
    }


    SDL_Event e;
    bool running = true;

    // Drawing Scratch Sprite!
    Sprite cat{};
    cat.texture = loadTexture(m_renderer, "cat.png");
    cat.rect = {400,250,200,200};
    cat.dragging = false;
    CodeTab.active = true;

    // Drawing the logo (top, right, corner)
    SDL_Texture* logoTex = loadTexture(m_renderer, "logo.png");

    while(running) {
        while(SDL_PollEvent(&e)) {
            // Events:
            if(e.type == SDL_QUIT)
                running = false;
            // Drag Sprite
            handleSpriteEvent(cat, e);

            // Clicking on tabs
            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mx = e.button.x;
                int my = e.button.y;

                // Changing the position by clicking
                if(isInside(mx, my, CodeTab.rect)) {
                    CodeTab.active = true;
                    CustomTab.active = SoundTab.active = false;
                }
                else if (isInside(mx, my, CustomTab.rect)) {
                    CustomTab.active = true;
                    CodeTab.active = SoundTab.active = false;
                }
                else if(isInside(mx, my, SoundTab.rect)) {
                    SoundTab.active = true;
                    CodeTab.active = CustomTab.active = false;
                }
                else if(isInside(mx, my, File.rect)) {
                    File.active = !File.active;
                    Edit.active = false;
                }
                else if(isInside(mx, my, Edit.rect)) {
                    Edit.active = !Edit.active;
                    File.active = false;
                }
                else if(isInside(mx,my,motionBtn.area)) {
                    motionBtn.active = true;
                }
                // else: continue
            }
        }
        // Render codes
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);
        drawTitleBar(m_renderer, m_window);

        // Drawing the logo
        drawStaticImage(m_renderer, logoTex, 20, 2, 110, 46);

        // Drawing file & edit tabs
        drawTab(m_renderer, font, File);
        drawTab(m_renderer, font, Edit);

        // Drawing Code, Custom, Sound tabs
        drawTab(m_renderer, font, CodeTab);
        drawTab(m_renderer, font, CustomTab);
        drawTab(m_renderer, font, SoundTab);

        // Drawing codeMenu buttons
        if(CodeTab.active) {
            drawSideButton(m_renderer, font, motionBtn);
            drawSideButton(m_renderer, font, looksBtn);
            drawSideButton(m_renderer, font, soundBtn);
            drawSideButton(m_renderer, font, eventsBtn);
            drawSideButton(m_renderer, font, controlBtn);
            drawSideButton(m_renderer, font, sensingBtn);
            drawSideButton(m_renderer, font, operatorsBtn);
            drawSideButton(m_renderer, font, variablesBtn);
        }

        // Drawing character
        drawCat(m_renderer, cat);


        SDL_RenderPresent(m_renderer);
        SDL_Delay(16);
    }

    // Destroy objects to save out memory
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}