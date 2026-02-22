#ifndef INC_14041016_LOOKS_H
#define INC_14041016_LOOKS_H

#include "UI_Objects.h"
static int globalLooksBlock = 3000;

SideButton looksBtn = {
        1,
        "Looks",
        {153,102,255,255},
        {0,155,70,65},
        false
};

void initLooks(SDL_Renderer* renderer) {
    // png blocks
    SDL_Texture* sayHelloForTex = IMG_LoadTexture(renderer, "sayHelloFor.png");
    SDL_Texture* sayHelloTex = IMG_LoadTexture(renderer, "sayHello.png");
    SDL_Texture* thinkForTex = IMG_LoadTexture(renderer, "thinkFor.png");
    SDL_Texture* thinkTex = IMG_LoadTexture(renderer, "think.png");
    SDL_Texture* switchCostumeTex = IMG_LoadTexture(renderer, "switchCostume.png");
    SDL_Texture* nextCostumeTex = IMG_LoadTexture(renderer, "nextCostume.png");
    SDL_Texture* switchBackdropTex = IMG_LoadTexture(renderer, "switchBackdrop.png");
    SDL_Texture* nextBackdropTex = IMG_LoadTexture(renderer, "nextBackdrop.png");
    SDL_Texture* changeSizeTex = IMG_LoadTexture(renderer, "changeSize.png");
    SDL_Texture* setSizeTex = IMG_LoadTexture(renderer, "setSize.png");
    SDL_Texture* changeColorTex = IMG_LoadTexture(renderer, "changeColor.png");
    SDL_Texture* setColorTex = IMG_LoadTexture(renderer, "setColor.png");
    SDL_Texture* clearGraphicTex = IMG_LoadTexture(renderer, "clearGraphicColor.png");
    SDL_Texture* showTex = IMG_LoadTexture(renderer, "show.png");
    SDL_Texture* hideTex = IMG_LoadTexture(renderer, "hide.png");
    SDL_Texture* goToFrontTex = IMG_LoadTexture(renderer, "goToFront.png");
    SDL_Texture* goForwardTex = IMG_LoadTexture(renderer, "goForward.png");

    int startY = 80, gap = 30;

    // sayHello for --- seconds
    LooksMenuBlocks.push_back({
                                      sayHelloForTex,
                                      {80, startY+11, 190, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // sayHello
    LooksMenuBlocks.push_back({
                                      sayHelloTex,
                                      {80, startY+gap+22, 80, 40},
                                      false, 0,0,
                                      false,
                                      -1,
                                      globalLooksBlock
                              });

    //think
    LooksMenuBlocks.push_back({
                                      thinkTex,
                                      {80, startY+gap*3, 90, 45},
                                      false, 0, 0,
                                      false,
                                      -1,
                                      globalLooksBlock
                              });

    // switch costume block
    DraggableBlock switchCostumeBlock = {
            switchCostumeTex,
            {80, startY+gap*4, 210, 45},
            false, 0,0,
            false,
            -1,
            globalLooksBlock++
    };
    switchCostumeBlock.hasDropdown = true;
    switchCostumeBlock.dropdownOptions = {"costume1", "costume2", "costume3"};
    switchCostumeBlock.dropdownRect = {0,0,100,22};
    LooksMenuBlocks.push_back(switchCostumeBlock);


    // next costume
    LooksMenuBlocks.push_back({
                                      nextCostumeTex,
                                      {80, startY+gap*5, 100, 45},
                                      false, 0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    DraggableBlock switchBackdropBlock = {
            switchBackdropTex,
            {80, startY+gap*6, 220, 45},
            false,0,0,
            false,
            -1,
            globalLooksBlock++
    };
    switchBackdropBlock.hasDropdown = true;
    switchBackdropBlock.dropdownOptions = {"backdrop1", "backdrop2"};
    switchBackdropBlock.dropdownRect = {0,0,100,22};
    LooksMenuBlocks.push_back(switchBackdropBlock);

    // next backdrop
    LooksMenuBlocks.push_back({
                                      nextBackdropTex,
                                      {80, startY+gap*7, 100, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // change size by
    LooksMenuBlocks.push_back({
                                      changeSizeTex,
                                      {80,startY+gap*8, 170, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // set size to
    LooksMenuBlocks.push_back({
                                      setSizeTex,
                                      {80,startY+gap*9, 160, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // change color effect
    LooksMenuBlocks.push_back({
                                      changeColorTex,
                                      {80,startY+gap*10,200,45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // set color effect
    LooksMenuBlocks.push_back({
                                      setColorTex,
                                      {80, startY+gap*11, 190, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // clear graphic effects
    LooksMenuBlocks.push_back({
                                      clearGraphicTex,
                                      {80, startY+gap*12, 190, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // show
    LooksMenuBlocks.push_back({
                                      showTex,
                                      {80, startY+gap*13-22, 50, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // hide
    LooksMenuBlocks.push_back({
                                      hideTex,
                                      {80, startY+gap*14-22, 50, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // go to front layer
    LooksMenuBlocks.push_back({
                                      goToFrontTex,
                                      {80, startY+gap*15-22, 180, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });

    // go forward layers
    LooksMenuBlocks.push_back({
                                      goForwardTex,
                                      {80, startY+gap*16-22, 200, 45},
                                      false,0,0,
                                      false,
                                      -1,
                                      globalLooksBlock++
                              });
}

void handleLooksBlock(SDL_Event& e, bool codeTabActive, bool looksBtnActive) {
    if(!codeTabActive || !looksBtnActive)
        return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        bool caught = false;
        for(int i = workspaceBlocks.size()-1; i >= 0; i--) {
            if(isInside(mx, my, workspaceBlocks[i].rect)) {

                if(handleNumberInputClick(mx,my,i))
                    return;

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

        if(!caught && codeTabActive && looksBtnActive) {
            for(auto& mb:LooksMenuBlocks) {
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

void renderLooksBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool looksBtnActive) {
    if(!codeTabActive || !looksBtnActive)
        return;
    if(codeTabActive && looksBtnActive) {
        for(auto& mb : LooksMenuBlocks) {
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

#endif //INC_14041016_LOOKS_H
