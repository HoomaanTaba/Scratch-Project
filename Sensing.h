#ifndef INC_14041016_SENSING_H
#define INC_14041016_SENSING_H

#include "UI_Objects.h"
static int globalSensingBlockID = 7000;
SideButton sensingBtn = {
        1,
        "Sensing",
        {76,191,230,255},
        {0,415,70,65},
        false
};

void initSensing(SDL_Renderer* renderer) {
    SDL_Texture* touchingTex = IMG_LoadTexture(renderer, "touching.png");
    SDL_Texture* touchingColorTex = IMG_LoadTexture(renderer, "touchingColor.png");
    SDL_Texture* colorTouchingColorTex = IMG_LoadTexture(renderer, "colorTouchingColor.png");
    SDL_Texture* distanceTex = IMG_LoadTexture(renderer, "distance.png");
    SDL_Texture* askTex = IMG_LoadTexture(renderer, "ask.png");
    SDL_Texture* answerTex = IMG_LoadTexture(renderer, "answer.png");
    SDL_Texture* keyPressedTex = IMG_LoadTexture(renderer, "keyPressed(2).png");
    SDL_Texture* mouseDownTex = IMG_LoadTexture(renderer, "mouseDown.png");
    SDL_Texture* mouseXTex = IMG_LoadTexture(renderer, "mouseX.png");
    SDL_Texture* mouseYTex = IMG_LoadTexture(renderer, "mouseY.png");
    SDL_Texture* setDragModeTex = IMG_LoadTexture(renderer, "setDragMode.png");
    SDL_Texture* loudnessTex = IMG_LoadTexture(renderer, "loudness(2).png");
    SDL_Texture* timerTex = IMG_LoadTexture(renderer, "timer.png");
    SDL_Texture* resetTimerTex = IMG_LoadTexture(renderer, "resetTimer.png");
    SDL_Texture* currentTex = IMG_LoadTexture(renderer, "current.png");
    SDL_Texture* attributeOfTex = IMG_LoadTexture(renderer, "attribute.png");
    SDL_Texture* daysSince2000Tex = IMG_LoadTexture(renderer, "daysSince2000.png");
    SDL_Texture* usernameTex = IMG_LoadTexture(renderer, "username.png");

    int startY = 100, gap = 28;

    // touching
    DraggableBlock touchingBlock = {
            touchingTex,
            {80, startY, 180, 40},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    touchingBlock.hasDropdown = true;
    touchingBlock.dropdownOptions = {"mouse-pointer","edge", "Sprite1"};
    touchingBlock.dropdownRect = {0,0,110,22};
    SensingMenuBlocks.push_back(touchingBlock);

    //touching color
    SensingMenuBlocks.push_back({
        touchingColorTex,
        {80,startY+gap,200,40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    //color is touching color?
    SensingMenuBlocks.push_back({
        colorTouchingColorTex,
        {80,startY+gap*2, 220, 40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // distanceBlock
    DraggableBlock distanceBlock = {
            distanceTex,
            {80, startY+gap*3, 190,40},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    distanceBlock.hasDropdown = true;
    distanceBlock.dropdownOptions = {"mouse-pointer","Sprite1"};
    distanceBlock.dropdownRect = {0,0,110,22};
    SensingMenuBlocks.push_back(distanceBlock);


    // ask and wait
    SensingMenuBlocks.push_back({
        askTex,
        {80,startY+gap*4, 220,40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // answer
    SensingMenuBlocks.push_back({
        answerTex,
        {80,startY+gap*5, 80,30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });

    // key pressed?
    DraggableBlock keyBlock = {
            keyPressedTex,
            {80, startY+gap*6, 190,40},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    keyBlock.hasDropdown = true;
    keyBlock.dropdownOptions = {"space","up arrow", "down arrow", "left arrow", "right arrow", "a", "b", "c"};
    keyBlock.dropdownRect = {0,0,110,22};
    SensingMenuBlocks.push_back(keyBlock);


    // mouse down?
    SensingMenuBlocks.push_back({
        mouseDownTex,
        {80, startY+gap*7,100, 40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // mouse x
    SensingMenuBlocks.push_back({
        mouseXTex,
        {80,startY+gap*8, 80,30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // mouse y
    SensingMenuBlocks.push_back({
        mouseYTex,
        {80,startY+gap*9, 80,30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    //set drag mode
    DraggableBlock dragModeBlock = {
            setDragModeTex,
            {80,startY+gap*10,200,40},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    dragModeBlock.hasDropdown = true;
    dragModeBlock.dropdownOptions = {"draggable", "not draggable"};
    dragModeBlock.dropdownRect = {0,0,130,22};
    SensingMenuBlocks.push_back(dragModeBlock);

    // loudness
    SensingMenuBlocks.push_back({
        loudnessTex,
        {80,startY+gap*11,80,30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });

    // timer
    SensingMenuBlocks.push_back({
        timerTex,
        {80, startY+gap*12, 65, 30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // reset timer
    SensingMenuBlocks.push_back({
        resetTimerTex,
        {80,startY+gap*13, 90, 40},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });


    // current
    DraggableBlock currentBlock = {
            currentTex,
            {80, startY+gap*14,140, 30},
            false,0,0,
            false,
            -1,
            globalSensingBlockID++
    };
    currentBlock.hasDropdown = true;
    currentBlock.dropdownOptions = {"year","month", "date", "day of week", "hour", "minute", "second"};
    currentBlock.dropdownRect = {0,0,120,22};
    SensingMenuBlocks.push_back(currentBlock);


    // attribute
    DraggableBlock attributeBlock = {
            attributeOfTex,
            {80, startY+gap*15, 200,30},
            false,0,0,
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
    attributeBlock.dropdownRect = {0,0,130,22};
    SensingMenuBlocks.push_back(attributeBlock);


    // days since 2000
    SensingMenuBlocks.push_back({
        daysSince2000Tex,
        {80,startY+gap*16,90,30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });

    // username
    SensingMenuBlocks.push_back({
        usernameTex,
        {80,startY+gap*17, 80, 30},
        false,0,0,
        false,
        -1,
        globalSensingBlockID++
    });
}


void handleSensingBlock(SDL_Event& e, bool codeTabActive, bool sensingBtnActive) {
    if(!codeTabActive || !sensingBtnActive)
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

        if(!caught && codeTabActive && sensingBtnActive) {
            for(auto& mb:SensingMenuBlocks) {
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

void renderSensingBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool sensingBtnActive) {
    if(!codeTabActive || !sensingBtnActive)
        return;
    if(codeTabActive && sensingBtnActive) {
        for(auto& mb : SensingMenuBlocks) {
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

#endif //INC_14041016_SENSING_H
