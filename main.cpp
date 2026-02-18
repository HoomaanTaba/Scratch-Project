#include "bits/stdc++.h"
#include "UI_Objects.h"
#include "Motion.h"
#include "Looks.h"
#include "Sound.h"
#include "Events.h"
#include "Control.h"
#include "Sensing.h"
#include "Operators.h"
#include "Variables.h"
using namespace std;

vector<DraggableBlock> workspaceBlocks;

vector<DraggableBlock> EventMenuBlocks;
vector<DraggableBlock> SoundMenuBlocks;
vector<DraggableBlock> LooksMenuBlocks;
vector<DraggableBlock> MotionMenuBlocks;
vector<DraggableBlock> ControlMenuBlocks;
vector<DraggableBlock> SensingMenuBlocks;
vector<DraggableBlock> OperatorMenuBlocks;
vector<DraggableBlock> VariablesMenuBlocks;

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
    cat.rect = {700,250,150,150};
    cat.dragging = false;
    CodeTab.active = true;

    // Drawing the logo (top, right, corner)
    SDL_Texture* logoTex = loadTexture(m_renderer, "logo.png");

    // Events - CodeMenu
    initEvents(m_renderer);
    // Sound - CodeMenu
    initSound(m_renderer);
    // Looks = CodeMenu
    initLooks(m_renderer);
    // Motion
    initMotion(m_renderer);

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
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = soundBtn.active = controlBtn.active = sensingBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,looksBtn.area)) {
                    looksBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = motionBtn.active = soundBtn.active = controlBtn.active = sensingBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,soundBtn.area)) {
                    soundBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = motionBtn.active = controlBtn.active = sensingBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,eventsBtn.area)) {
                    eventsBtn.active = true;
                    // make other menus unactive
                    motionBtn.active = looksBtn.active = soundBtn.active = controlBtn.active = sensingBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,controlBtn.area)) {
                    controlBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = soundBtn.active = motionBtn.active = sensingBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,sensingBtn.area)) {
                    sensingBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = soundBtn.active = controlBtn.active = motionBtn.active = operatorsBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,operatorsBtn.area)) {
                    operatorsBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = soundBtn.active = controlBtn.active = sensingBtn.active = motionBtn.active = variablesBtn.active = false;
                }
                else if(isInside(mx,my,variablesBtn.area)) {
                    variablesBtn.active = true;
                    // make other menus unactive
                    eventsBtn.active = looksBtn.active = soundBtn.active = controlBtn.active = sensingBtn.active = operatorsBtn.active = motionBtn.active = false;
                }
            }
            // Events - CodeMenu
            if(CodeTab.active && eventsBtn.active)
                handleEventBlock(e, CodeTab.active, eventsBtn.active);
            // Sound - CodeMenu
            else if(CodeTab.active && soundBtn.active)
                handleSoundBlock(e, CodeTab.active, soundBtn.active);
            // Looks - CodeMenu
            else if(CodeTab.active && looksBtn.active)
                handleLooksBlock(e,CodeTab.active,looksBtn.active);
            // Motion = CodeMenu
            else if(CodeTab.active && motionBtn.active)
                handleMotionBlock(e,CodeTab.active,motionBtn.active);
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

            renderEventBlocks(m_renderer, font, CodeTab.active, eventsBtn.active);
            renderSoundBlocks(m_renderer, font, CodeTab.active, soundBtn.active);
            renderLooksBlocks(m_renderer, font, CodeTab.active, looksBtn.active);
            renderMotionBlocks(m_renderer, font, CodeTab.active, motionBtn.active);
        }

        // Drawing character
        drawCat(m_renderer, cat);

        // Presenting and delay
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
