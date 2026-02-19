#ifndef INC_14041016_VARIABLES_H
#define INC_14041016_VARIABLES_H

#include "UI_Objects.h"
SideButton variablesBtn = {
        1,
        "Variables",
        {255,140,26,255},
        {0,545,70,65},
        false
};

void initVariables(SDL_Renderer* renderer) {
    SDL_Texture* variableTex = IMG_LoadTexture(renderer, "variable.png");
    SDL_Texture* setVarTex = IMG_LoadTexture(renderer, "setVar.png");
    SDL_Texture* changeVarTex = IMG_LoadTexture(renderer, "changeVar.png");
    SDL_Texture* showVarTex = IMG_LoadTexture(renderer, "showVar.png");
    SDL_Texture* hideVarTex = IMG_LoadTexture(renderer, "hideVar.png");

    int startY = 100, gap = 55;


    // Variable
    VariablesMenuBlocks.push_back({
        variableTex,
        {80, startY, 80, 30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // set variable
    DraggableBlock setBlock = {
            setVarTex,
            {80, startY+gap,170,40},
            false,0,0,
            false,-1,
            globalSensingBlockID++
    };
    setBlock.hasDropdown = true;
    setBlock.dropdownOptions = {"myVariable"};
    setBlock.dropdownRect = {0,0,100,22};
    VariablesMenuBlocks.push_back(setBlock);

    // change variable
    DraggableBlock changeBlock = {
            changeVarTex,
            {80, startY+gap*2, 180, 40},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    changeBlock.hasDropdown = true;
    changeBlock.dropdownOptions = {"myVariable"};
    changeBlock.dropdownRect = {0,0,100,22};
    VariablesMenuBlocks.push_back(changeBlock);

    // show variable
    VariablesMenuBlocks.push_back({
        showVarTex,
        {80, startY+gap*3, 150, 40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });

    // hide
    VariablesMenuBlocks.push_back({
        hideVarTex,
        {80, startY+gap*4, 150, 40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });
}


void handleVariablesBlock(SDL_Event& e, bool codeTabActive, bool variablesBtnActive) {
    if(!codeTabActive || !variablesBtnActive)
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

        if(!caught && codeTabActive && variablesBtnActive) {
            for(auto& mb:VariablesMenuBlocks) {
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

void renderVariablesBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool variablesBtnActive) {
    if(!codeTabActive || !variablesBtnActive)
        return;
    if(codeTabActive && variablesBtnActive) {
        for(auto& mb : VariablesMenuBlocks) {
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


#endif //INC_14041016_VARIABLES_H
