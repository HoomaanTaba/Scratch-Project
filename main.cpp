#include "bits/stdc++.h"
#include "UI_Objects.h"
#include "Motion.h"
#include "Looks.h"
#include "Sound.h"
#include "Event.h"
#include "Control.h"
#include "Sensing.h"
#include "Operators.h"
#include "Variables.h"
using namespace std;

void executeBlockChain(int startID, Sprite& sprite, Stage& stage) {
    int currentID = startID;

    while (true) {
        DraggableBlock* block = nullptr;
        for (auto& b : workspaceBlocks) {
            if (b.id == currentID) {
                block = &b;
            }
        }
        if (!block)
            break;

        switch (block->blockType) {
            // Looks
            case BLOCK_SHOW:
                show(sprite);
                break;
            case BLOCK_HIDE:
                hide(sprite);
                break;
            case BLOCK_CHANGE_SIZE: {
                double val = block->inputText1.empty() ? block->inputValue : atof(block->inputText1.c_str());
                change_size_by(sprite, val);
                break;
            }
            case BLOCK_SET_SIZE: {
                double val = block->inputText1.empty() ? block->inputValue : atof(block->inputText1.c_str());
                set_size(sprite, val);
                break;
            }
            case BLOCK_SWITCH_COSTUME:
                switch_costume_to(sprite, block->selectedOption);
                break;
            case BLOCK_SWITCH_BACKDROP:
                switch_backdrop_to(stage, block->selectedOption);
                break;
            case BLOCK_SAY:
                say(sprite, block->inputText1);
                break;
            case BLOCK_SAY_FOR: {
                int time = atoi(block->inputText2.c_str());
                say_for_seconds(sprite, block->inputText1, time);
                break;
            }
            case BLOCK_THINK:
                think(sprite, block->inputText1);
                break;
            case BLOCK_THINK_FOR:
            {
                int time = atoi(block->inputText2.c_str());
                think_for_seconds(sprite, block->inputText1, time);
                break;
            }
            case BLOCK_NEXT_COSTUME:
                next_costume(sprite, (int)sprite.costumeNames.size());
                break;
            case BLOCK_NEXT_BACKDROP:
                next_backdrop(stage);
                break;
            case BLOCK_CHANGE_EFFECT:
                change_effect(sprite, block->dropdownOptions[block->selectedOption], block->inputValue);
                break;
            case BLOCK_SET_EFFECT_TO:
                set_effect(sprite, block->dropdownOptions[block->selectedOption], block->inputValue);
                break;
            case BLOCK_CLEAR_EFFECT:
                clear_graphic_effects(sprite);
                break;
            case BLOCK_GO_TO_FRONT_LAYER:
                go_to_front(sprite, stage.sprites);
                break;
            case BLOCK_GO_TO_BACK_LAYER:
                go_to_back(sprite, stage.sprites);
                break;
            case BLOCK_GO_FORWARD_LAYERS:

                go_forward_layers(sprite, stage.sprites, block->inputValue);
                break;
            case BLOCK_GO_BACKWARD_LAYERS:
                go_backward_layers(sprite, stage.sprites, block->inputValue);
                break;
            case BLOCK_REPORT_BACKDROP_NUMBER: {
                double value = get_backdrop_number(stage);
                block->reporterOutput = std::to_string(value);
                break;
            }
            case BLOCK_REPORT_BACKDROP_NAME: {
                string name = get_backdrop_name(stage);
                block->reporterOutput = name;
                break;
            }
            case BLOCK_REPORT_COSTUME_NAME: {
                string name = get_costume_name(sprite);
                block->reporterOutput = name;
                break;
            }
            case BLOCK_REPORT_COSTUME_NUMBER: {
                double value = get_costume_number(sprite);
                block->reporterOutput = std::to_string(value);
                break;
            }
            case BLOCK_REPORT_SIZE: {
                double value = get_size(sprite);
                block->reporterOutput = std::to_string(value);
                break;
            }

            //Motion
            case BLOCK_MOVE:
                move_n_steps(sprite, block->inputValue);
                break;
            case BLOCK_TURN_RIGHT:
                turn_angle_right(sprite, block->inputValue);
                break;
            case BLOCK_TURN_LEFT:
                turn_angle_left(sprite, block->inputValue);
                break;
            case BLOCK_GO_TO_XY:
                go_to_x_and_y(sprite, block->inputValue, block->inputValue2);
                break;
            case BLOCK_GO_TO_RANDOM:
                go_to_randomposition(sprite);
                break;
            case BLOCK_GO_TO_MOUSE:
                go_to_mouseposition(sprite);
                break;
            case BLOCK_CHANGE_X:
                change_x_by(sprite, block->inputValue);
                break;
            case BLOCK_CHANGE_Y:
                change_y_by(sprite, block->inputValue);
                break;
            case BLOCK_POINT_DIRECTION:
                point_in_direction(sprite, block->inputValue);
                break;
            case BLOCK_SET_X:
                set_x_to(sprite, block->inputValue);
                break;
            case BLOCK_SET_Y:
                set_y_to(sprite, block->inputValue);
                break;


            // Sensing
            case BLOCK_TOUCHING: {
                bool result = false;

                if (block->dropdownOptions[block->selectedOption] == "mouse-pointer")
                    result = touchingMouse(sprite);

                else if (block->dropdownOptions[block->selectedOption] == "edge")
                    result = touchingEdge(sprite);

                else {
                    if (!stage.sprites.empty())
                        result = touchingSprite(sprite, *stage.sprites[0]);
                }

                cout << "Touching result: " << result << endl;
            }
                break;

            case BLOCK_DISTANCE: {
                double d = 0;

                if (block->dropdownOptions[block->selectedOption] == "mouse-pointer") {
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    d = distanceTo(sprite.x, sprite.y, mx, my);
                }
                else {
                    if (!stage.sprites.empty())
                        d = distanceToSprite(sprite, *stage.sprites[0]);
                }

                cout << "Distance: " << d << endl;
            }
                break;
            case BLOCK_ASK_AND_WAIT:
                askQuestion(sprite, block->inputMessage);
                break;
            case BLOCK_KEY_PRESSED: {
                SDL_Scancode code = SDL_SCANCODE_SPACE;

                if (block->dropdownOptions[block->selectedOption] == "up arrow")
                    code = SDL_SCANCODE_UP;
                else if (block->dropdownOptions[block->selectedOption] == "down arrow")
                    code = SDL_SCANCODE_DOWN;
                else if (block->dropdownOptions[block->selectedOption] == "left arrow")
                    code = SDL_SCANCODE_LEFT;
                else if (block->dropdownOptions[block->selectedOption] == "right arrow")
                    code = SDL_SCANCODE_RIGHT;
                else if (block->dropdownOptions[block->selectedOption] == "space")
                    code = SDL_SCANCODE_SPACE;
                else if (block->dropdownOptions[block->selectedOption] == "any")
                    code = SDL_SCANCODE_RETURN;
                else if (block->dropdownOptions[block->selectedOption] == "a")
                    code = SDL_SCANCODE_A;
                else if (block->dropdownOptions[block->selectedOption] == "b")
                    code = SDL_SCANCODE_B;
                else if (block->dropdownOptions[block->selectedOption] == "c")
                    code = SDL_SCANCODE_C;
                else if (block->dropdownOptions[block->selectedOption] == "d")
                    code = SDL_SCANCODE_D;
                else if (block->dropdownOptions[block->selectedOption] == "e")
                    code = SDL_SCANCODE_E;
                else if (block->dropdownOptions[block->selectedOption] == "f")
                    code = SDL_SCANCODE_F;
                else if (block->dropdownOptions[block->selectedOption] == "g")
                    code = SDL_SCANCODE_G;
                else if (block->dropdownOptions[block->selectedOption] == "h")
                    code = SDL_SCANCODE_H;
                else if (block->dropdownOptions[block->selectedOption] == "i")
                    code = SDL_SCANCODE_I;
                else if (block->dropdownOptions[block->selectedOption] == "j")
                    code = SDL_SCANCODE_J;
                else if (block->dropdownOptions[block->selectedOption] == "k")
                    code = SDL_SCANCODE_K;
                else if (block->dropdownOptions[block->selectedOption] == "l")
                    code = SDL_SCANCODE_L;
                else if (block->dropdownOptions[block->selectedOption] == "m")
                    code = SDL_SCANCODE_M;
                else if (block->dropdownOptions[block->selectedOption] == "n")
                    code = SDL_SCANCODE_N;
                else if (block->dropdownOptions[block->selectedOption] == "o")
                    code = SDL_SCANCODE_O;
                else if (block->dropdownOptions[block->selectedOption] == "p")
                    code = SDL_SCANCODE_P;
                else if (block->dropdownOptions[block->selectedOption] == "q")
                    code = SDL_SCANCODE_Q;
                else if (block->dropdownOptions[block->selectedOption] == "r")
                    code = SDL_SCANCODE_R;
                else if (block->dropdownOptions[block->selectedOption] == "s")
                    code = SDL_SCANCODE_S;
                else if (block->dropdownOptions[block->selectedOption] == "t")
                    code = SDL_SCANCODE_T;
                else if (block->dropdownOptions[block->selectedOption] == "u")
                    code = SDL_SCANCODE_U;
                else if (block->dropdownOptions[block->selectedOption] == "v")
                    code = SDL_SCANCODE_V;
                else if (block->dropdownOptions[block->selectedOption] == "w")
                    code = SDL_SCANCODE_W;
                else if (block->dropdownOptions[block->selectedOption] == "x")
                    code = SDL_SCANCODE_X;
                else if (block->dropdownOptions[block->selectedOption] == "y")
                    code = SDL_SCANCODE_Y;
                else if (block->dropdownOptions[block->selectedOption] == "z")
                    code = SDL_SCANCODE_Z;
                else if (block->dropdownOptions[block->selectedOption] == "1")
                    code = SDL_SCANCODE_1;
                else if (block->dropdownOptions[block->selectedOption] == "2")
                    code = SDL_SCANCODE_2;
                else if (block->dropdownOptions[block->selectedOption] == "3")
                    code = SDL_SCANCODE_3;
                else if (block->dropdownOptions[block->selectedOption] == "4")
                    code = SDL_SCANCODE_4;
                else if (block->dropdownOptions[block->selectedOption] == "5")
                    code = SDL_SCANCODE_5;
                else if (block->dropdownOptions[block->selectedOption] == "6")
                    code = SDL_SCANCODE_6;
                else if (block->dropdownOptions[block->selectedOption] == "7")
                    code = SDL_SCANCODE_7;
                else if (block->dropdownOptions[block->selectedOption] == "8")
                    code = SDL_SCANCODE_8;
                else if (block->dropdownOptions[block->selectedOption] == "9")
                    code = SDL_SCANCODE_9;
                else if (block->dropdownOptions[block->selectedOption] == "0")
                    code = SDL_SCANCODE_0;

                bool pressed = keyPressed(code);
                cout << pressed << endl;
            }
                break;
            case BLOCK_MOUSE_DOWN:
                cout<<mouseDown()<<endl;
                break;
            case BLOCK_TIMER:
                cout<<timerValue()<<endl;
                break;
            case BLOCK_RESET_TIMER:
                resetTimer();
                break;
            case BLOCK_TOUCHING_COLOR: {
                SDL_Color testColor = {0,255,0,255}; //testing
                bool result = touchingColor(sprite, testColor);
                cout <<"Touching Color: "<< result << endl;
            }
                break;
            case BLOCK_COLOR_TOUCHING_COLOR: {
                SDL_Color c1 = {0,0,255,255};
                SDL_Color c2 = {255,0,0,255};

                if (!stage.sprites.empty()) {
                    bool result = colorTouchingColor(sprite, c1, *stage.sprites[0], c2);
                    cout <<"Color Touching Color: "<< result << endl;
                }
            }
                break;
            case BLOCK_ANSWER:
                cout<<"Answer: "<<getAnswer()<<endl;
                break;
            case BLOCK_MOUSE_X:
                cout<<"Mouse X: "<< mouseX() << endl;
                break;
            case BLOCK_MOUSE_Y:
                cout<<"Mouse Y: "<< mouseY() << endl;
                break;
            case BLOCK_SET_DRAG_MODE: {
                string mode = block->dropdownOptions[block->selectedOption];

                if (mode == "draggable")
                    sprite.dragging = true;
                else
                    sprite.dragging = false;

                cout<<"Drag mode set to: "<< mode << endl;
            }
                break;

        }
        sprite.rect.x = (int)sprite.x;
        sprite.rect.y = (int)sprite.y;
        //finding next block
        int nextID = -1;
        for (auto& b : workspaceBlocks) {
            if (b.parentID == block->id)
                nextID = b.id;
        }
        if (nextID == -1)
            break;

        currentID = nextID;
    }
}
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
    cat.visible = true;
    cat.texture = loadTexture(m_renderer, "cat.png");
    cat.rect = {700,250,150,150};
    cat.x = cat.rect.x;
    cat.y = cat.rect.y;
    cat.dragging = false;
    Stage stage;
    stage.backdrops.push_back(loadTexture(m_renderer, "backdrop1.png"));
    stage.backdropNames.push_back("backdrop1");

    stage.backdrops.push_back(loadTexture(m_renderer, "backdrop2.png"));
    stage.backdropNames.push_back("backdrop2");

    stage.sprites.push_back(&cat);
    CodeTab.active = true;

    initTimer();

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
    // Sensing
    initSensing(m_renderer);

    srand(time(NULL));
    while(running) {
        while(SDL_PollEvent(&e)) {
            // Events:
            if(e.type == SDL_QUIT)
                running = false;
            // Drag Sprite
            handleSpriteEvent(cat, e);
            handleTextInput(e);

            if (e.type == SDL_TEXTINPUT) {
                for (auto& wb : workspaceBlocks) {
                    if (wb.editingInput1)
                        wb.inputText1 += e.text.text;
                    if (wb.editingInput2)
                        wb.inputText2 += e.text.text;
                }
            }

             if (e.type == SDL_KEYDOWN) {
                 if (e.key.keysym.sym == SDLK_BACKSPACE) {
                     for (auto& wb : workspaceBlocks) {
                         if (wb.editingInput1 && !wb.inputText1.empty())
                             wb.inputText1.pop_back();

                         if (wb.editingInput2 && !wb.inputText2.empty())
                             wb.inputText2.pop_back();
                     }
                 }

                 if (e.key.keysym.sym == SDLK_RETURN) {
                     for (auto& wb : workspaceBlocks) {


                         if (wb.editingInput1) {
                             // if the block has text
                             if (wb.hasTextInput)
                                 wb.inputMessage = wb.inputText1;
                             else
                                 wb.inputValue = atof(wb.inputText1.c_str());

                             wb.editingInput1 = false;
                         }

                         if (wb.editingInput2) {
                             wb.inputValue2 = atof(wb.inputText2.c_str());
                             wb.editingInput2 = false;
                         }
                     }
                     SDL_StopTextInput();
                 }
             }

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
            else if (CodeTab.active && sensingBtn.active)
                handleSensingBlock(e, CodeTab.active, sensingBtn.active);
        }

        // =========================== EXECUTION ENGINE ====================
        for (auto& b : workspaceBlocks) {
            if (b.isHat)
                executeBlockChain(b.id, cat, stage);
        }
        // =================================================================
        // Render codes
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);

        renderStage(m_renderer, stage);
        update_message(cat);
        render_message(cat, m_renderer, font);

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
            renderSensingBlocks(m_renderer, font, CodeTab.active, sensingBtn.active);

        }
        // ============= RENDER WORKSPACE BLOCKS ================
        for (auto& b : workspaceBlocks) {
            SDL_RenderCopy(m_renderer, b.texture, NULL, &b.rect);

            // Draw reporter output if exists
            if (!b.reporterOutput.empty()) {
                SDL_Color color = {20,20,20,255};

                SDL_Surface* surf = TTF_RenderUTF8_Blended(
                    font,
                    b.reporterOutput.c_str(),
                    color
                );

                if (surf) {
                    SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, surf);
                    SDL_Rect outRect;
                    outRect.w = surf->w;
                    outRect.h = surf->h;
                    outRect.x = b.rect.x + 10;
                    outRect.y = b.rect.y + b.rect.h + 4;

                    SDL_RenderCopy(m_renderer, text, NULL, &outRect);

                    SDL_FreeSurface(surf);
                    SDL_DestroyTexture(text);
                }
            }
        }

        // Drawing character

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