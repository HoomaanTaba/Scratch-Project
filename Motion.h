#ifndef INC_14041016_MOTION_H
#define INC_14041016_MOTION_H

#include "UI_Objects.h"
static int globalMotionBlockID = 5000;

SideButton motionBtn = {
        1,
        "Motion",
        {76,151,255,255},
        {0,90,70,65},
        true
};

void initMotion(SDL_Renderer* renderer) {
    SDL_Texture* moveTex = IMG_LoadTexture(renderer, "move.png");
    SDL_Texture* turnRightTex = IMG_LoadTexture(renderer, "turnRight.png");
    SDL_Texture* turnLeftTex = IMG_LoadTexture(renderer, "turnLeft.png");
    SDL_Texture* goToXYTex = IMG_LoadTexture(renderer, "goToXY.png");
    SDL_Texture* goToTex = IMG_LoadTexture(renderer, "goTo.png");
    SDL_Texture* glideTex = IMG_LoadTexture(renderer, "glide.png");
    SDL_Texture* pointDirTex = IMG_LoadTexture(renderer, "pointDir.png");
    SDL_Texture* pointTowardsTex = IMG_LoadTexture(renderer, "pointTowards.png");
    SDL_Texture* changeXTex = IMG_LoadTexture(renderer, "changeX.png");
    SDL_Texture* setXTex = IMG_LoadTexture(renderer, "setX.png");
    SDL_Texture* changeYTex = IMG_LoadTexture(renderer, "changeY.png");
    SDL_Texture* setYTex = IMG_LoadTexture(renderer, "setY.png");
    SDL_Texture* bounceTex = IMG_LoadTexture(renderer, "bounce.png");
    SDL_Texture* rotationTex = IMG_LoadTexture(renderer, "rotation.png");

    int startY = 100, gap = 35;

    // Move block
    MotionMenuBlocks.push_back({
        moveTex,
        {80, startY, 130, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    });

    // turn right
    MotionMenuBlocks.push_back({
        turnRightTex,
        {80, startY+gap, 150, 45},
        false, 0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // turn left
    MotionMenuBlocks.push_back({
        turnLeftTex,
        {80, startY+gap*2, 150, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    });

    // go to xy
    MotionMenuBlocks.push_back({
        goToXYTex,
        {80, startY+gap*3, 150, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // go to (dropdown)
    DraggableBlock goToBlock = {
            goToTex,
            {80, startY+gap*4, 160, 45},
            false,0,0,
            false,
            -1,
            globalMotionBlockID++
    };
    goToBlock.hasDropdown = true;
    goToBlock.dropdownOptions = {"mouse-pointer", "random position", "sprite1"};
    goToBlock.dropdownRect = {0,0,100,22};
    MotionMenuBlocks.push_back(goToBlock);

    // glide
    MotionMenuBlocks.push_back({
        glideTex,
        {80, startY+gap*5, 230, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // point in direction
    MotionMenuBlocks.push_back({
        pointDirTex,
        {80, startY+gap*6, 150, 45},
        false, 0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    DraggableBlock pointTowardsBlock = {
            pointTowardsTex,
            {80, startY+gap*7, 200, 45},
            false,0,0,
            false,
            -1,
            globalMotionBlockID++
    };
    pointTowardsBlock.hasDropdown = true;
    pointTowardsBlock.dropdownOptions = {"mouse-pointer", "sprite1"};
    pointTowardsBlock.dropdownRect = {0,0,100,22};
    MotionMenuBlocks.push_back(pointTowardsBlock);

    // change x
    MotionMenuBlocks.push_back({
        changeXTex,
        {80, startY+gap*8, 110, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // set x
    MotionMenuBlocks.push_back({
        setXTex,
        {80, startY+gap*9, 110, 45},
        false, 0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // change y
    MotionMenuBlocks.push_back({
        changeYTex,
        {80, startY+gap*10, 110, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // set y
    MotionMenuBlocks.push_back({
        setYTex,
        {80, startY+gap*11, 110, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // bounce
    MotionMenuBlocks.push_back({
        bounceTex,
        {80, startY+gap*12, 130, 45},
        false,0,0,
        false,
        -1,
        globalMotionBlockID++
    });

    // set rotation style (dropdown)
    DraggableBlock rotationBlock = {
            rotationTex,
            {80, startY+gap*13, 200, 45},
            false,0,0,
            false,
            -1,
            globalMotionBlockID++
    };
    rotationBlock.hasDropdown = true;
    rotationBlock.dropdownOptions = {"all around", "left-right", "don't rotate"};
    rotationBlock.dropdownRect = {0,0,120,22};
    MotionMenuBlocks.push_back(rotationBlock);
}

void handleMotionBlock(SDL_Event& e, bool codeTabActive, bool motionBtnActive) {
    if(!codeTabActive || !motionBtnActive)
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

        if(!caught && codeTabActive && motionBtnActive) {
            for(auto& mb:MotionMenuBlocks) {
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

void renderMotionBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool motionBtnActive) {
    if(!codeTabActive || !motionBtnActive)
        return;
    if(codeTabActive && motionBtnActive) {
        for(auto& mb : MotionMenuBlocks) {
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
        // input number on blocks
        if(wb.hasNumberInput) {
            SDL_Rect absInput {
                wb.rect.x + wb.inputRect.x,
                wb.rect.y + wb.inputRect.y,
                wb.inputRect.x,
                wb.inputRect.h
            };

            SDL_Color textColor = wb.isTyping ? SDL_Color{0,0,255} : SDL_Color{0,0,0};
            drawTextCentered(renderer, font, wb.inputStr, absInput, textColor);
        }
    }
}

#endif //INC_14041016_MOTION_H
