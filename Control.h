#ifndef SCRATCH_CONTROLUI_H
#define SCRATCH_CONTROLUI_H
#include "UI_Objects.h"
static int globalControlBlockID = 6000;
// SideButton of control orders in code menu
SideButton controlBtn = {
        1,
        "Control",
        {255,171,25,255},
        {0,350,70,65},
        false
};

void initControl(SDL_Renderer* renderer) {
    // Hat Blocks
    SDL_Texture* foreverTex = IMG_LoadTexture(renderer, "Forever.png");
    SDL_Texture* ifTex  = IMG_LoadTexture(renderer, "IF.png");
    SDL_Texture* if_elseTex  = IMG_LoadTexture(renderer, "IF_ELSE.png");
    SDL_Texture* stopTex  = IMG_LoadTexture(renderer, "STOP.png");
    SDL_Texture* waitTex=IMG_LoadTexture(renderer,"WAIT.png");
    SDL_Texture* wait_untilTex  = IMG_LoadTexture(renderer, "WAIT_UNTIL.png");
    SDL_Texture* repeatTex  = IMG_LoadTexture(renderer, "REPEAT.png");
    SDL_Texture* repeat_untilTex  = IMG_LoadTexture(renderer, "REPEAT_UNTIL.png");

    int startY = 100,gap = 70;

    // forever block

    ControlMenuBlocks.push_back({
                                        foreverTex,
                                        {80, startY-5, 130, 70},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        ifTex,
                                        {80, startY+gap, 130, 70},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        if_elseTex,
                                        {80, startY+gap*2, 130, 100},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        stopTex,
                                        {80, startY+gap*7-20, 110, 35},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    DraggableBlock stopBlock = {
            stopTex,
            {80,startY+gap*7,140,40},
            false,
            0,
            0,
            false,
            -1,
            globalControlBlockID++
    };
    ControlMenuBlocks.push_back({
                                        waitTex,
                                        {80, startY+gap*3+30, 130, 40},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        wait_untilTex,
                                        {80, startY+gap*5, 120, 40},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        repeatTex,
                                        {80, startY+gap*4, 130, 70},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
    ControlMenuBlocks.push_back({
                                        repeat_untilTex,
                                        {80, startY+gap*6-20, 120, 70},
                                        false, 0, 0,
                                        false,
                                        -1,
                                        globalControlBlockID++
                                });
}
void handleControlBlock(SDL_Event& e, bool codeTabActive, bool ControlBtnActive) {
    if(!codeTabActive || !ControlBtnActive) return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        bool caught = false;
        for(int i = workspaceBlocks.size()-1; i >= 0; i--) {
            if(isInside(mx, my, workspaceBlocks[i].rect)) {
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

        if(!caught && codeTabActive && ControlBtnActive) {
            for(auto& mb:ControlMenuBlocks) {
                if(isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;

                    newNode.parentID = -1;
                    newNode.dragging = true;

                    newNode.rect.x = mx - mb.rect.w/2;
                    newNode.rect.y = my - mb.rect.h/2;

                    newNode.offsetX = mb.rect.w/2;
                    newNode.offsetY = mb.rect.h/2;
                    workspaceBlocks.push_back(newNode);
                    break;
                }
            }
        }
    }


    if(e.type == SDL_MOUSEBUTTONUP) {
        for(auto& b : workspaceBlocks) {
            if(b.dragging) {
                b.dragging = false;
                if(b.rect.x < 250) {
                    for(int k = 0; k < workspaceBlocks.size(); k++) {
                        if(&workspaceBlocks[k]==&b) {
                            workspaceBlocks.erase(workspaceBlocks.begin() + k);
                            break;
                            return;
                        }
                    }
                }
                // Sticking part

                for(auto& target : workspaceBlocks) {
                    if(&b == &target)
                        continue;

                    int centerBX = b.rect.x + b.rect.w/2;
                    int centerTX = target.rect.x + target.rect.w/2;

                    int snapX = abs(centerBX - centerTX);
                    int snapY = abs(b.rect.y - (target.rect.y + target.rect.h));

                    if(snapX < 30 && snapY < 30) {
                        if(b.isHat && target.parentID != -1)
                            continue;
                        b.rect.x = target.rect.x;
                        b.rect.y = target.rect.y + target.rect.h-6; //Overlapping pixels
                        b.parentID = target.id;
                        break; // when fined good block, break;
                    }
                }
            }
        }
    }
    if(e.type == SDL_MOUSEMOTION) {
        for(int i = 0; i < workspaceBlocks.size(); i++) {
            if(workspaceBlocks[i].dragging) {
                int oldX = workspaceBlocks[i].rect.x;
                int oldY = workspaceBlocks[i].rect.y;

                // Dragging the main block
                workspaceBlocks[i].rect.x = mx - workspaceBlocks[i].offsetX;
                workspaceBlocks[i].rect.y = my - workspaceBlocks[i].offsetY;

                // no come in stage
                if(workspaceBlocks[i].rect.x + workspaceBlocks[i].rect.w > 600)
                    workspaceBlocks[i].rect.x = 600 - workspaceBlocks[i].rect.w;

                // no come in title bar
                if(workspaceBlocks[i].rect.y < 90)
                    workspaceBlocks[i].rect.y = 90;

                // no exit from the bottom
                if(workspaceBlocks[i].rect.y + workspaceBlocks[i].rect.h > 610)
                    workspaceBlocks[i].rect.y = 610 - workspaceBlocks[i].rect.h;

                int diffX = workspaceBlocks[i].rect.x - oldX;
                int diffY = workspaceBlocks[i].rect.y - oldY;

                // Dragging all blocks under each other
                bool changed = true;
                vector<int> movedIndices;
                movedIndices.push_back(i);
                while(changed) {
                    changed = false;
                    for(int j = 0; j < workspaceBlocks.size(); j++) {
                        bool alreadyMoved = false;
                        for(int idx: movedIndices)
                            if(idx==j)
                                alreadyMoved = true;
                        if(!alreadyMoved && j != i && !workspaceBlocks[j].dragging) {
                            for(int idx: movedIndices) {
                                // checking if idx is under a block
                                if(workspaceBlocks[j].parentID == workspaceBlocks[idx].id && workspaceBlocks[j].parentID != -1) {
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

void renderControlBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool controlBtnActive) {
    if(!codeTabActive || !controlBtnActive)
        return;
    if(codeTabActive && controlBtnActive) {
        for(auto& mb : ControlMenuBlocks) {
            SDL_RenderCopy(renderer, mb.texture, NULL, &mb.rect);
        }
    }
    for(auto& wb : workspaceBlocks) {
        SDL_RenderCopy(renderer, wb.texture, NULL, &wb.rect);
        if(wb.hasDropdown) {
            wb.dropdownRect.x = wb.rect.x + wb.rect.w - 100;
            wb.dropdownRect.y = wb.rect.y + 18;

            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            SDL_RenderFillRect(renderer, &wb.dropdownRect);

            SDL_SetRenderDrawColor(renderer, 150,150,150,255);
            SDL_RenderDrawRect(renderer, &wb.dropdownRect);

            SDL_Color textColor = {0,0,0,255};
            drawTextCentered(renderer,font,
                             wb.dropdownOptions[wb.selectedOption],
                             wb.dropdownRect,
                             textColor);

            if(wb.dropdownOpen) {
                for(int i = 0; i < wb.dropdownOptions.size(); i++) {
                    SDL_Rect optionRect = {
                            wb.dropdownRect.x,
                            wb.dropdownRect.y + (i+1)*wb.dropdownRect.h,
                            wb.dropdownRect.w,
                            wb.dropdownRect.h
                    };

                    SDL_SetRenderDrawColor(renderer, 240,240,240,255);
                    SDL_RenderFillRect(renderer, &optionRect);
                    SDL_RenderDrawRect(renderer, &optionRect);

                    drawTextCentered(renderer, font,
                                     wb.dropdownOptions[i],
                                     optionRect,
                                     textColor);
                }
            }
        }
    }
}


#endif //SCRATCH_CONTROLUI_H
