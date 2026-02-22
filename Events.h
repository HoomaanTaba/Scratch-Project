#ifndef INC_14041016_EVENTS_H
#define INC_14041016_EVENTS_H

#include "UI_Objects.h"


// GRAPHIC PART


static int globalEventBlockID = 1000;
// SideButton of events in code menu
SideButton eventsBtn = {
        1,
        "Events",
        {255,213,64,255},
        {0,285,70,65},
        false
};

void initEvents(SDL_Renderer* renderer) {
    // Hat Blocks
    SDL_Texture* greenFlagTex = IMG_LoadTexture(renderer, "greenFlag.png");
    SDL_Texture* keyPressTex  = IMG_LoadTexture(renderer, "keyPressed.png");
    SDL_Texture* spriteClickTex  = IMG_LoadTexture(renderer, "spriteClick.png");
    SDL_Texture* backdropTex  = IMG_LoadTexture(renderer, "backDrop.png");
    SDL_Texture* loudnessTex  = IMG_LoadTexture(renderer, "loudness.png");
    SDL_Texture* receiveTex  = IMG_LoadTexture(renderer, "receive.png");

    // Command Blocks
    SDL_Texture* broadcastTex  = IMG_LoadTexture(renderer, "broadcast.png");
    SDL_Texture* broadcastWaitTex  = IMG_LoadTexture(renderer, "broadcastWait.png");

    int startY = 100, gap = 55;

    // when green flag
    EventMenuBlocks.push_back({
          greenFlagTex,
             {80, startY, 140, 50},
             false, 0, 0,
             true,
             -1,
             globalEventBlockID++
    });

    // when key press
    DraggableBlock keyBlock = {
            keyPressTex,
            {80, startY+gap, 150, 50},
            false, 0, 0,
            true,
            -1,
            globalEventBlockID++
    };
    keyBlock.hasDropdown = true;
    keyBlock.dropdownOptions = {"space", "up arrow", "down arow", "a", "b", "c"};
    keyBlock.dropdownRect = {0,0,80,20};
    EventMenuBlocks.push_back(keyBlock);

    // when sprite clicked
    EventMenuBlocks.push_back({
             spriteClickTex,
             {80, startY+gap*2, 145, 50},
             false, 0, 0,
             true,
             -1,
             globalEventBlockID++
    });

    // when backdrop switches (dropdown)
    DraggableBlock backdropBlock = {
            backdropTex,
            {80, startY+gap*3, 165, 50},
            false, 0, 0,
            true,
            -1,
            globalEventBlockID++
    };
    backdropBlock.hasDropdown = true;
    backdropBlock.dropdownOptions = {"backdrop1", "backdrop2"};
    backdropBlock.dropdownRect = {0,0,80,20};
    EventMenuBlocks.push_back(backdropBlock);

    // when loudness
    DraggableBlock loudnessBlock = {
            loudnessTex,
            {80, startY+gap*4, 155,50},
            false,0,0,
            true,
            -1,
            globalEventBlockID++
    };
    loudnessBlock.hasDropdown = true;
    loudnessBlock.dropdownOptions = {"message1", "message2", "message3"};
    loudnessBlock.dropdownRect = {0,0,60,20};

    loudnessBlock.hasNumberInput = true;
    loudnessBlock.inputStr = "10";
    // white circle geo
    loudnessBlock.inputRect = {120, 15,30,20};
    EventMenuBlocks.push_back(loudnessBlock);

    // when I receive
    DraggableBlock receiveBlock = {
            receiveTex,
            {80, startY+gap*5, 155, 50},
            false, 0, 0,
            true,
            -1,
            globalEventBlockID++
    };
    receiveBlock.hasDropdown = true;
    receiveBlock.dropdownOptions = {"message1", "message2", "message3"};
    receiveBlock.dropdownRect = {0,0,90,20};
    EventMenuBlocks.push_back(receiveBlock);

    // broadcast
    DraggableBlock broadcastBlock = {
            broadcastTex,
            {80, startY+gap*6, 140, 40},
            false, 0, 0,
            false,
            -1,
            globalEventBlockID++
    };
    broadcastBlock.hasDropdown = true;
    broadcastBlock.dropdownOptions = {"message1", "message2", "message3"};
    broadcastBlock.dropdownRect = {0,0,90,20};
    EventMenuBlocks.push_back(broadcastBlock);

    // broadcast and wait
    DraggableBlock broadcastWaitBlock = {
            broadcastWaitTex,
            {80, startY+gap*7, 160, 40},
            false, 0, 0,
            false,
            -1,
            globalEventBlockID++
    };
    broadcastWaitBlock.hasDropdown = true;
    broadcastWaitBlock.dropdownOptions = {"message1", "message2", "message3"};
    broadcastWaitBlock.dropdownRect = {0,0,90,20};
    EventMenuBlocks.push_back(broadcastWaitBlock);
}

void handleEventBlock(SDL_Event& e, bool codeTabActive, bool eventBtnActive) {
    if(!codeTabActive || !eventBtnActive)
        return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        bool caught = false;
        for(int i = workspaceBlocks.size()-1; i >= 0; i--) {
            if(isInside(mx, my, workspaceBlocks[i].rect)) {
                if(handleNumberInputClick(mx,my,i))
                    return;
                // typical dragging
                int oldParent = workspaceBlocks[i].parentID;
                if(oldParent != -1) {
                    for(auto& b : workspaceBlocks) {
                        if(b.id == oldParent) {
                            b.nextID = -1;
                            break;
                        }
                    }
                }
                workspaceBlocks[i].offsetX = mx - workspaceBlocks[i].rect.x;
                workspaceBlocks[i].offsetY = my - workspaceBlocks[i].rect.y;

                DraggableBlock temp = workspaceBlocks[i];
                workspaceBlocks.erase(workspaceBlocks.begin() + i);
                workspaceBlocks.push_back(temp);
                caught = true;

                // cancel typing by clicking outside textbox
                for(auto& b: workspaceBlocks)
                    if(&b != &workspaceBlocks.back())
                        b.isTyping = false;

                break;
            }
        }

        if(!caught && codeTabActive && eventBtnActive) {
            for(auto& mb:EventMenuBlocks) {
                if(isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;
                    newNode.id = globalSoundBlockID++;
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
                        }
                    }
                    return;
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
                        target.nextID = b.id;
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

void renderEventBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool eventBtnActive) {
    if(!codeTabActive || !eventBtnActive)
        return;
    if(codeTabActive && eventBtnActive) {
        for(auto& mb : EventMenuBlocks) {
            SDL_RenderCopy(renderer, mb.texture, NULL, &mb.rect);
        }
    }
    for(auto& wb : workspaceBlocks) {
        SDL_RenderCopy(renderer, wb.texture, NULL, &wb.rect);


        if(wb.hasNumberInput) {
            SDL_Rect absInput {
                wb.rect.x + wb.inputRect.x,
                wb.rect.y + wb.inputRect.y,
                wb.inputRect.w,
                wb.inputRect.h
            };
            SDL_Color textColor = {0,0,0};
            if(wb.isTyping)
                textColor = {0,0,255};

            drawTextCentered(renderer, font, wb.inputStr, absInput, textColor);
        }


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
#endif //INC_14041016_EVENTS_H
