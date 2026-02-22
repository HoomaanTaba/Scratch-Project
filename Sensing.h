//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_SENSING_H
#define SCRATCH_SENSING_H


#include "UI_Objects.h"
#include <cmath>
#include <string>
static int globalSensingBlockID = 7000;
SideButton sensingBtn = {
    1,
    "Sensing",
    {76, 191, 230, 255},
    {0, 415, 70, 65},
    false
};

#define BLOCK_TOUCHING               700
#define BLOCK_TOUCHING_COLOR         701
#define BLOCK_COLOR_TOUCHING_COLOR   702
#define BLOCK_DISTANCE               703
#define BLOCK_ASK_AND_WAIT           704
#define BLOCK_ANSWER                 705
#define BLOCK_KEY_PRESSED            706
#define BLOCK_MOUSE_DOWN             707
#define BLOCK_MOUSE_X                708
#define BLOCK_MOUSE_Y                709
#define BLOCK_SET_DRAG_MODE          710
#define BLOCK_TIMER                  711
#define BLOCK_RESET_TIMER            712
#define BLOCK_LOUDNESS               713

void initSensing(SDL_Renderer *renderer) {
    SDL_Texture *touchingTex = IMG_LoadTexture(renderer, "touching.png");
    SDL_Texture *touchingColorTex = IMG_LoadTexture(renderer, "touchingColor.png");
    SDL_Texture *colorTouchingColorTex = IMG_LoadTexture(renderer, "colorTouchingColor.png");
    SDL_Texture *distanceTex = IMG_LoadTexture(renderer, "distance.png");
    SDL_Texture *askTex = IMG_LoadTexture(renderer, "ask.png");
    SDL_Texture *answerTex = IMG_LoadTexture(renderer, "answer.png");
    SDL_Texture *keyPressedTex = IMG_LoadTexture(renderer, "keyPressed(2).png");
    SDL_Texture *mouseDownTex = IMG_LoadTexture(renderer, "mouseDown.png");
    SDL_Texture *mouseXTex = IMG_LoadTexture(renderer, "mouseX.png");
    SDL_Texture *mouseYTex = IMG_LoadTexture(renderer, "mouseY.png");
    SDL_Texture *setDragModeTex = IMG_LoadTexture(renderer, "setDragMode.png");
    SDL_Texture *loudnessTex = IMG_LoadTexture(renderer, "loudness(2).png");
    SDL_Texture *timerTex = IMG_LoadTexture(renderer, "timer.png");
    SDL_Texture *resetTimerTex = IMG_LoadTexture(renderer, "resetTimer.png");
    SDL_Texture *currentTex = IMG_LoadTexture(renderer, "current.png");
    SDL_Texture *attributeOfTex = IMG_LoadTexture(renderer, "attribute.png");
    SDL_Texture *daysSince2000Tex = IMG_LoadTexture(renderer, "daysSince2000.png");
    SDL_Texture *usernameTex = IMG_LoadTexture(renderer, "username.png");

    int startY = 100, gap = 28;

    // touching
    DraggableBlock touchingBlock = {
        touchingTex,
        {80, startY, 180, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    touchingBlock.blockType = BLOCK_TOUCHING;
    touchingBlock.hasDropdown = true;
    touchingBlock.selectedOption = 0;
    touchingBlock.dropdownOptions = {"mouse-pointer", "edge", "Sprite1"};
    touchingBlock.dropdownRect = {0, 0, 110, 22};
    SensingMenuBlocks.push_back(touchingBlock);

    //touching color
    DraggableBlock touchingColorBlock = {
        touchingColorTex,
        {80, startY + gap, 200, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    touchingColorBlock.blockType = BLOCK_TOUCHING_COLOR;
    touchingColorBlock.hasTextInput = true;
    touchingColorBlock.inputRect1 = {0, 0, 80, 22};
    SensingMenuBlocks.push_back(touchingColorBlock);


    //color is touching color?
    DraggableBlock colorTouchingBlock = {
        colorTouchingColorTex,
        {80, startY + gap * 2, 220, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    colorTouchingBlock.blockType = BLOCK_COLOR_TOUCHING_COLOR;
    colorTouchingBlock.hasTextInput = true;
    colorTouchingBlock.hasSecondNumberInput = false;
    colorTouchingBlock.editingInput2 = false;
    colorTouchingBlock.inputRect1 = {0, 0, 70, 22};
    colorTouchingBlock.inputRect2 = {0, 0, 70, 22};
    SensingMenuBlocks.push_back(colorTouchingBlock);


    // distanceBlock
    DraggableBlock distanceBlock = {
        distanceTex,
        {80, startY + gap * 3, 190, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    distanceBlock.blockType = BLOCK_DISTANCE;
    distanceBlock.hasDropdown = true;
    distanceBlock.selectedOption = 0;
    distanceBlock.dropdownOptions = {"mouse-pointer", "Sprite1"};
    distanceBlock.dropdownRect = {0, 0, 110, 22};
    SensingMenuBlocks.push_back(distanceBlock);


    // ask and wait
    DraggableBlock askBlock = {
        askTex,
        {80, startY + gap * 4, 220, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    askBlock.blockType = BLOCK_ASK_AND_WAIT;
    askBlock.hasTextInput = true;
    askBlock.inputRect1 = {0, 0, 100, 22};
    SensingMenuBlocks.push_back(askBlock);


    // answer
    DraggableBlock answerBlock = {
        answerTex,
        {80, startY + gap * 5, 80, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    answerBlock.blockType = BLOCK_ANSWER;
    SensingMenuBlocks.push_back(answerBlock);

    // key pressed?
    DraggableBlock keyBlock = {
        keyPressedTex,
        {80, startY + gap * 6, 190, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    keyBlock.blockType = BLOCK_KEY_PRESSED;
    keyBlock.hasDropdown = true;
    keyBlock.selectedOption = 0;
    keyBlock.dropdownOptions = {"space", "up arrow", "down arrow", "left arrow", "right arrow", "a", "b", "c"};
    keyBlock.dropdownRect = {0, 0, 110, 22};
    SensingMenuBlocks.push_back(keyBlock);


    // mouse down?
    DraggableBlock mouseDownBlock = {
        mouseDownTex,
        {80, startY + gap * 7, 100, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    mouseDownBlock.blockType = BLOCK_MOUSE_DOWN;
    SensingMenuBlocks.push_back(mouseDownBlock);


    // mouse x
    DraggableBlock mouseXBlock = {
        mouseXTex,
        {80, startY + gap * 8, 80, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    mouseXBlock.blockType = BLOCK_MOUSE_X;
    SensingMenuBlocks.push_back(mouseXBlock);


    // mouse y
    DraggableBlock mouseYBlock = {
        mouseYTex,
        {80, startY + gap * 9, 80, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    mouseYBlock.blockType = BLOCK_MOUSE_Y;
    SensingMenuBlocks.push_back(mouseYBlock);


    //set drag mode
    DraggableBlock dragModeBlock = {
        setDragModeTex,
        {80, startY + gap * 10, 200, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    dragModeBlock.blockType = BLOCK_SET_DRAG_MODE;
    dragModeBlock.hasDropdown = true;
    dragModeBlock.selectedOption = 0;
    dragModeBlock.dropdownOptions = {"draggable", "not draggable"};
    dragModeBlock.dropdownRect = {0, 0, 130, 22};
    SensingMenuBlocks.push_back(dragModeBlock);

    // loudness
    DraggableBlock loudBlock = {
        loudnessTex,
        {80, startY + gap * 11, 80, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    loudBlock.blockType = BLOCK_LOUDNESS;
    SensingMenuBlocks.push_back(loudBlock);

    // timer
    DraggableBlock timerBlock = {
        timerTex,
        {80, startY + gap * 12, 65, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    timerBlock.blockType = BLOCK_TIMER;
    SensingMenuBlocks.push_back(timerBlock);


    // reset timer
    DraggableBlock resetTimerBlock = {
        resetTimerTex,
        {80, startY + gap * 13, 90, 40},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    resetTimerBlock.blockType = BLOCK_RESET_TIMER;
    SensingMenuBlocks.push_back(resetTimerBlock);


    // current
    DraggableBlock currentBlock = {
        currentTex,
        {80, startY + gap * 14, 140, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    currentBlock.hasDropdown = true;
    currentBlock.dropdownOptions = {"year", "month", "date", "day of week", "hour", "minute", "second"};
    currentBlock.dropdownRect = {0, 0, 120, 22};
    SensingMenuBlocks.push_back(currentBlock);


    // attribute
    DraggableBlock attributeBlock = {
        attributeOfTex,
        {80, startY + gap * 15, 200, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    };
    attributeBlock.hasDropdown = true;
    attributeBlock.dropdownOptions = {
        "x position",
        "y position",
        "direction",
        "costume #",
        "costume name",
        "size",
        "volume",
        "backdrop #",
        "backdrop name"
    };
    attributeBlock.dropdownRect = {0, 0, 130, 22};
    SensingMenuBlocks.push_back(attributeBlock);


    // days since 2000
    SensingMenuBlocks.push_back({
        daysSince2000Tex,
        {80, startY + gap * 16, 90, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    });

    // username
    SensingMenuBlocks.push_back({
        usernameTex,
        {80, startY + gap * 17, 80, 30},
        false, 0, 0,
        false,
        -1,
        globalSensingBlockID++
    });
}


void handleSensingBlock(SDL_Event &e, bool codeTabActive, bool sensingBtnActive) {
    if (!codeTabActive || !sensingBtnActive)
        return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (auto &b: workspaceBlocks) {
            if (b.hasDropdown) {
                if (isInside(mx, my, b.dropdownRect)) {
                    b.dropdownOpen = !b.dropdownOpen;
                    return;
                }

                if (b.dropdownOpen) {
                    for (int i = 0; i < b.dropdownOptions.size(); ++i) {
                        SDL_Rect optionRect = {
                            b.dropdownRect.x,
                            b.dropdownRect.y + (i + 1) * b.dropdownRect.h,
                            b.dropdownRect.w,
                            b.dropdownRect.h
                        };

                        if (isInside(mx, my, optionRect)) {
                            b.selectedOption = i;
                            b.dropdownOpen = false;
                            return;
                        }
                    }
                }
            }
        }
        // Text Input Detection
        for (auto &b: workspaceBlocks) {
            if (b.hasTextInput) {
                b.inputRect1.x = b.rect.x + 60;
                b.inputRect1.y = b.rect.y + 8;

                if (isInside(mx, my, b.inputRect1)) {
                    b.editingInput1 = true;
                    SDL_StartTextInput();
                    return;
                }
            }

            if (b.hasSecondNumberInput) {
                b.inputRect2.x = b.rect.x + 130;
                b.inputRect2.y = b.rect.y + 8;

                if (isInside(mx, my, b.inputRect2)) {
                    b.editingInput2 = true;
                    SDL_StartTextInput();
                    return;
                }
            }
        }


        bool caught = false;
        for (int i = workspaceBlocks.size() - 1; i >= 0; i--) {
            if (isInside(mx, my, workspaceBlocks[i].rect)) {
                workspaceBlocks[i].dragging = true;
                workspaceBlocks[i].parentID = -1;
                workspaceBlocks[i].offsetX = mx - workspaceBlocks[i].rect.x;
                workspaceBlocks[i].offsetY = my - workspaceBlocks[i].rect.y;

                DraggableBlock temp = workspaceBlocks[i];
                workspaceBlocks.erase(workspaceBlocks.begin() + i);
                workspaceBlocks.push_back(temp);
                caught = true;
                break;
            }
        }

        if (!caught && codeTabActive && sensingBtnActive) {
            for (auto &mb: SensingMenuBlocks) {
                if (isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;

                    newNode.parentID = -1;
                    newNode.dragging = true;

                    newNode.rect.x = mx - mb.rect.w / 2;
                    newNode.rect.y = my - mb.rect.h / 2;

                    newNode.offsetX = mb.rect.w / 2;
                    newNode.offsetY = mb.rect.h / 2;
                    workspaceBlocks.push_back(newNode);
                    break;
                }
            }
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        for (auto &b: workspaceBlocks) {
            if (b.dragging) {
                b.dragging = false;
                if (b.rect.x < 250) {
                    for (int k = 0; k < workspaceBlocks.size(); k++) {
                        if (&workspaceBlocks[k] == &b) {
                            workspaceBlocks.erase(workspaceBlocks.begin() + k);
                            break;
                            return;
                        }
                    }
                }
                // Sticking part

                for (auto &target: workspaceBlocks) {
                    if (&b == &target)
                        continue;

                    int centerBX = b.rect.x + b.rect.w / 2;
                    int centerTX = target.rect.x + target.rect.w / 2;

                    int snapX = abs(centerBX - centerTX);
                    int snapY = abs(b.rect.y - (target.rect.y + target.rect.h));

                    if (snapX < 30 && snapY < 30) {
                        if (b.isHat && target.parentID != -1)
                            continue;
                        b.rect.x = target.rect.x;
                        b.rect.y = target.rect.y + target.rect.h - 6; //Overlapping pixels
                        b.parentID = target.id;
                        break; // when fined good block, break;
                    }
                }
            }
        }
    }
    if (e.type == SDL_MOUSEMOTION) {
        for (int i = 0; i < workspaceBlocks.size(); i++) {
            if (workspaceBlocks[i].dragging) {
                int oldX = workspaceBlocks[i].rect.x;
                int oldY = workspaceBlocks[i].rect.y;

                // Dragging the main block
                workspaceBlocks[i].rect.x = mx - workspaceBlocks[i].offsetX;
                workspaceBlocks[i].rect.y = my - workspaceBlocks[i].offsetY;

                // no come in stage
                if (workspaceBlocks[i].rect.x + workspaceBlocks[i].rect.w > 600)
                    workspaceBlocks[i].rect.x = 600 - workspaceBlocks[i].rect.w;

                // no come in title bar
                if (workspaceBlocks[i].rect.y < 90)
                    workspaceBlocks[i].rect.y = 90;

                // no exit from the bottom
                if (workspaceBlocks[i].rect.y + workspaceBlocks[i].rect.h > 610)
                    workspaceBlocks[i].rect.y = 610 - workspaceBlocks[i].rect.h;

                int diffX = workspaceBlocks[i].rect.x - oldX;
                int diffY = workspaceBlocks[i].rect.y - oldY;

                // Dragging all blocks under each other
                bool changed = true;
                vector<int> movedIndices;
                movedIndices.push_back(i);
                while (changed) {
                    changed = false;
                    for (int j = 0; j < workspaceBlocks.size(); j++) {
                        bool alreadyMoved = false;
                        for (int idx: movedIndices)
                            if (idx == j)
                                alreadyMoved = true;
                        if (!alreadyMoved && j != i && !workspaceBlocks[j].dragging) {
                            for (int idx: movedIndices) {
                                // checking if idx is under a block
                                if (workspaceBlocks[j].parentID == workspaceBlocks[idx].id && workspaceBlocks[j].
                                    parentID != -1) {
                                    workspaceBlocks[j].rect.x += diffX;
                                    workspaceBlocks[j].rect.y += diffY;
                                    movedIndices.push_back(j);
                                    changed = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void renderSensingBlocks(SDL_Renderer *renderer, TTF_Font *font, bool codeTabActive, bool sensingBtnActive) {
    if (!codeTabActive || !sensingBtnActive)
        return;
    if (codeTabActive && sensingBtnActive) {
        for (auto &mb: SensingMenuBlocks) {
            SDL_RenderCopy(renderer, mb.texture, NULL, &mb.rect);
        }
    }
    for (auto &wb: workspaceBlocks) {
        SDL_RenderCopy(renderer, wb.texture, NULL, &wb.rect);
        if (wb.hasDropdown) {
            wb.dropdownRect.x = wb.rect.x + wb.rect.w - 100;
            wb.dropdownRect.y = wb.rect.y + 18;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &wb.dropdownRect);

            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderDrawRect(renderer, &wb.dropdownRect);

            SDL_Color textColor = {0, 0, 0, 255};
            drawTextCentered(renderer, font,
                             wb.dropdownOptions[wb.selectedOption],
                             wb.dropdownRect,
                             textColor);

            if (wb.dropdownOpen) {
                for (int i = 0; i < wb.dropdownOptions.size(); i++) {
                    SDL_Rect optionRect = {
                        wb.dropdownRect.x,
                        wb.dropdownRect.y + (i + 1) * wb.dropdownRect.h,
                        wb.dropdownRect.w,
                        wb.dropdownRect.h
                    };

                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                    SDL_RenderFillRect(renderer, &optionRect);
                    SDL_RenderDrawRect(renderer, &optionRect);

                    drawTextCentered(renderer, font,
                                     wb.dropdownOptions[i],
                                     optionRect,
                                     textColor);
                }
            }
        }

        if (wb.hasTextInput) {
            wb.inputRect1.x = wb.rect.x + 60;
            wb.inputRect2.y = wb.rect.y + 8;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &wb.inputRect1);

            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderDrawRect(renderer, &wb.inputRect1);

            SDL_Color c = {0, 0, 0, 255};
            drawTextCentered(renderer, font, wb.inputText1, wb.inputRect1, c);
        }
    }
}

static std::string g_answer;
static Uint32 g_timerStart = 0;

inline bool touchingSprite(Sprite &a, Sprite &b) {
    if (!a.visible || !b.visible)
        return false;
    return SDL_HasIntersection(&a.rect, &b.rect);
}

inline bool touchingMouse(Sprite &s) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    return mouseOnSprite(mx, my, s);
}

inline bool touchingEdge(Sprite &s) {
    if (s.rect.x <= 0) return true;
    if (s.rect.y <= 0) return true;
    if (s.rect.x + s.rect.w >= W) return true;
    if (s.rect.y + s.rect.h >= H) return true;

    return false;
}

inline bool touchingColor(Sprite &s, SDL_Color targetColor) {
    if (!s.visible || !s.surface) return false;

    SDL_Surface *surf = s.surface;

    SDL_LockSurface(surf);

    Uint32 *pixels = (Uint32 *) surf->pixels;

    for (int y = 0; y < surf->h; y++) {
        for (int x = 0; x < surf->w; x++) {
            Uint32 pixel = pixels[y * surf->w + x];

            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, surf->format, &r, &g, &b, &a);

            if (r == targetColor.r && g == targetColor.g && b == targetColor.b && a != 0) {
                SDL_UnlockSurface(surf);
                return true;
            }
        }
    }

    SDL_UnlockSurface(surf);
    return false;
}

inline bool colorTouchingColor(Sprite &a, SDL_Color c1, Sprite &b, SDL_Color c2) {
    return touchingSprite(a, b);
}

inline double distanceTo(double x1, double y1, double x2, double y2) {
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline double distanceToSprite(Sprite &a, Sprite &b) {
    return distanceTo(a.rect.x + a.rect.w / 2.0,
                      a.rect.y + a.rect.h / 2.0,
                      b.rect.x + b.rect.w / 2.0,
                      b.rect.y + b.rect.h / 2.0);
}

inline void askQuestion(Sprite &s, const std::string &question) {
    s.message = question;
    s.messageType = 1; //Say
    s.messageStartTime = SDL_GetTicks();
    s.messageDuration = 0; //wait until answer

    g_answer = "";
    SDL_StartTextInput();
}

inline void handleTextInput(SDL_Event &e) {
    if (e.type == SDL_TEXTINPUT) {
        g_answer = e.text.text;
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE) {
        if (!g_answer.empty())
            g_answer.pop_back();
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        SDL_StopTextInput();
    }
}

inline std::string getAnswer() {
    return g_answer;
}

inline bool keyPressed(SDL_Scancode code) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[code];
}

inline bool mouseDown() {
    Uint32 state = SDL_GetMouseState(NULL, NULL);
    return state & SDL_BUTTON(SDL_BUTTON_LEFT);
}

inline int mouseX() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    return mx;
}

inline int mouseY() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    return my;
}

inline void initTimer() {
    g_timerStart = SDL_GetTicks();
}

inline void resetTimer() {
    g_timerStart = SDL_GetTicks();
}

inline double timerValue() {
    Uint32 now = SDL_GetTicks();
    return (double) (now - g_timerStart) / 1000.0;
}

#endif //SCRATCH_SENSING_H
