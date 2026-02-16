#ifndef INC_14041016_SOUND_H
#define INC_14041016_SOUND_H

#include "UI_Objects.h"
static int globalSoundBlockID = 2000;

SideButton soundBtn = {
        1,
        "Sound",
        {214,92,214,255},
        {0,220,70,65},
        false
};

void initSound(SDL_Renderer* renderer) {
    // png blocks
    SDL_Texture* playTex        = IMG_LoadTexture(renderer, "playSound.png");
    SDL_Texture* playUntilTex   = IMG_LoadTexture(renderer, "playUntilDone.png");
    SDL_Texture* stopAllTex     = IMG_LoadTexture(renderer, "stopAllSounds.png");
    SDL_Texture* changePitchTex = IMG_LoadTexture(renderer, "changePitch.png");
    SDL_Texture* setPitchTex    = IMG_LoadTexture(renderer, "setPitch.png");
    SDL_Texture* changePanTex   = IMG_LoadTexture(renderer, "changePan.png");
    SDL_Texture* setPanTex      = IMG_LoadTexture(renderer, "setPan.png");
    SDL_Texture* clearEffectsTex = IMG_LoadTexture(renderer, "clearEffects.png");


    int startY = 100, gap = 55;

    // play sound
    DraggableBlock playBlock = {
            playTex,
            {80, startY, 180, 40},
            false, 0, 0,
            false,
            -1,
            globalSoundBlockID++
    };
    playBlock.hasDropdown = true;
    playBlock.dropdownOptions = {"meow", "pop", "beep"};
    playBlock.dropdownRect = {0,0,100,22};
    SoundMenuBlocks.push_back(playBlock);


    // play sound until done block
    DraggableBlock playUntilBlock = {
            playUntilTex,
            {80, startY+gap, 170, 40},
            false, 0, 0,
            false,
            -1,
            globalSoundBlockID++
    };
    playUntilBlock.hasDropdown = true;
    playUntilBlock.dropdownOptions = {"meow", "pop", "beep"};
    playUntilBlock.dropdownRect = {0,0,100,22};

    SoundMenuBlocks.push_back(playUntilBlock);


    // stop all sounds
    SoundMenuBlocks.push_back({
        stopAllTex,
        {80, startY+gap*2, 140, 40},
        false,0,0,
        false,
        -1,
        globalSoundBlockID++
    });


    // change pitch
    SoundMenuBlocks.push_back({
        changePitchTex,
        {80, startY+gap*3, 180,40},
        false,0,0,
        false,
        -1,
        globalSoundBlockID++
    });


    // set pitch
    SoundMenuBlocks.push_back({
        setPitchTex,
        {80, startY+gap*4, 170, 40},
        false, 0, 0,
        false,
        -1,
        globalSoundBlockID++
    });


    // change pan
    SoundMenuBlocks.push_back({
        changePanTex,
        {80, startY+gap*5, 160, 40},
        false, 0, 0,
        false,
        -1,
        globalSoundBlockID++
    });


    //set pan
    SoundMenuBlocks.push_back({
        setPanTex,
        {80,startY+gap*6,155,40},
        false,0,0,
        false,
        -1,
        globalSoundBlockID++
    });

    // clear Effects
    SoundMenuBlocks.push_back({
        clearEffectsTex,
        {80, startY+gap*7, 110, 40},
        false,0,0,
        false,
        -1,
        globalSoundBlockID++
    });
}

void handleSoundBlock(SDL_Event& e, bool codeTabActive, bool soundBtnActive) {
    if(!codeTabActive || !soundBtnActive)
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

        if(!caught && codeTabActive && soundBtnActive) {
            for(auto& mb:SoundMenuBlocks) {
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

void renderSoundBlocks(SDL_Renderer* renderer, TTF_Font* font, bool codeTabActive, bool soundBtnActive) {
    if(!codeTabActive || !soundBtnActive)
        return;
    if(codeTabActive && soundBtnActive) {
        for(auto& mb : SoundMenuBlocks) {
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

#endif //INC_14041016_SOUND_H
