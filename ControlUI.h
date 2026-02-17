
#ifndef SCRATCH_CONTROLUI_H
#define SCRATCH_CONTROLUI_H
#include "UI_Objects.h"
static int globalControlBlockID = 1000;
// SideButton of control orders in code menu
SideButton controlBtn = {
        1,
        "Control",
        {255,171,25,255},
        {0,350,70,65},
        true
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

    int startY = 100, gap = 55;

    // forever block
    ControlMenuBlocks.push_back({
          foreverTex,
             {80, startY, 150, 70},
             false, 0, 0,
             false,
             -1,
             globalControlBlockID++
    });

    // if block
    DraggableBlock ifBlock = {
            ifTex,
            {80, startY+gap, 150, 50},
            false, 0, 0,
            false,
            -1,
            globalControlBlockID++
    };
    ifBlock.hasDropdown = true;
    ifBlock.dropdownOptions = {"space", "up arrow", "down arow", "a", "b", "c"};
    ifBlock.dropdownRect = {0,0,80,20};
    ControlMenuBlocks.push_back(ifBlock);

    // when sprite clicked
    ControlMenuBlocks.push_back({
             ifTex,
             {80, startY+gap*2, 145, 50},
             false, 0, 0,
             true,
             -1,
             globalControlBlockID++
    });

    // if else block
    DraggableBlock if_elseBlock = {
            if_elseTex,
            {80, startY+gap*3, 160, 100},
            false, 0, 0,
            false,
            -1,
            globalControlBlockID++
    };
    if_elseBlock.hasDropdown = true;
    if_elseBlock.dropdownOptions = {"backdrop1", "backdrop2"};
    if_elseBlock.dropdownRect = {0,0,80,20};
    ControlMenuBlocks.push_back(if_elseBlock);

    // stop block
    ControlMenuBlocks.push_back({
             stopTex,
             {80, startY+gap*4, 145, 50},
             false, 0, 0,
             true,
             -1,
             globalControlBlockID++
    });

    // wait block
    DraggableBlock waitBlock = {
            waitTex,
            {80, startY+gap*5, 155, 50},
            false, 0, 0,
            true,
            -1,
            globalControlBlockID++
    };
    waitBlock.hasDropdown = true;
    waitBlock.dropdownOptions = {"message1", "message2", "message3"};
    waitBlock.dropdownRect = {0,0,90,20};
    ControlMenuBlocks.push_back(waitBlock);

    // wait until block
    DraggableBlock wait_untilBlock = {
            wait_untilTex,
            {80, startY+gap*6, 140, 40},
            false, 0, 0,
            false,
            -1,
            globalControlBlockID++
    };
    wait_untilBlock.hasDropdown = true;
    wait_untilBlock.dropdownOptions = {"message1", "message2", "message3"};
    wait_untilBlock.dropdownRect = {0,0,90,20};
    ControlMenuBlocks.push_back(wait_untilBlock);

    // repeat until block
    DraggableBlock repeat_untilBlock = {
            repeat_untilTex,
            {80, startY+gap*7, 160, 70},
            false, 0, 0,
            false,
            -1,
            globalControlBlockID++
    };
    repeat_untilBlock.hasDropdown = true;
    repeat_untilBlock.dropdownOptions = {"message1", "message2", "message3"};
    repeat_untilBlock.dropdownRect = {0,0,90,20};
    ControlMenuBlocks.push_back(repeat_untilBlock);
}

void handleControlBlock(SDL_Event& e, bool codeTabActive, bool controlBtnActive) {
    if(!codeTabActive || !controlBtnActive)
        return;
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

        if(!caught && codeTabActive && controlBtnActive) {
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