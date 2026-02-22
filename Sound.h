#ifndef INC_14041016_SOUND_H
#define INC_14041016_SOUND_H

// GRAPHIC PART

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
    playBlock.blockType = "play_sound";
    playBlock.dropdownOptions = {"meow", "pop", "beep"};
    playBlock.dropdownLocalRect = {70,8,50,22};
    SoundMenuBlocks.push_back(playBlock);


    // play sound until done block
    DraggableBlock playUntilBlock = {
            playUntilTex,
            {80, startY+gap, 140, 40},
            false, 0, 0,
            false,
            -1,
            globalSoundBlockID++
    };
    playUntilBlock.hasDropdown = true;
    playUntilBlock.blockType = "play_until_done";
    playUntilBlock.dropdownOptions = {"meow", "pop", "beep"};
    playUntilBlock.dropdownLocalRect = {80,8,50,22};

    SoundMenuBlocks.push_back(playUntilBlock);


    // stop all sounds
    DraggableBlock stopBlock = {
            stopAllTex,
            {80,startY+gap*2, 100,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    stopBlock.blockType = "stop_all";
    SoundMenuBlocks.push_back(stopBlock);


    // change pitch
    DraggableBlock changePitchBlock = {
            changePitchTex,
            {80, startY+gap*3,180,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    changePitchBlock.blockType = "change_pitch";
    changePitchBlock.hasNumberInput = true;
    changePitchBlock.inputRect = {143,7,35,20};
    changePitchBlock.hasDropdown = true;
    changePitchBlock.dropdownOptions = {"pitch", "pan"};
    changePitchBlock.dropdownLocalRect = {48,7,50,22};
    SoundMenuBlocks.push_back(changePitchBlock);


    // set pitch
    DraggableBlock setPitchBlock = {
            setPitchTex,
            {80,startY+gap*4,170,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    setPitchBlock.blockType = "set_pitch";
    setPitchBlock.hasNumberInput = true;
    setPitchBlock.inputRect = {130,8,35,20};
    setPitchBlock.hasDropdown = true;
    setPitchBlock.dropdownOptions = {"pitch", "pan"};
    setPitchBlock.dropdownLocalRect = {38,7,50,22};
    SoundMenuBlocks.push_back(setPitchBlock);



    // change pan
    DraggableBlock changePanBlock = {
            changePanTex,
            {80,startY+gap*5,140,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    changePanBlock.blockType = "change_pan";
    changePanBlock.hasNumberInput = true;
    changePanBlock.inputRect = {100,8,35,20};
    SoundMenuBlocks.push_back(changePanBlock);

    //set pan
    DraggableBlock setPanBlock = {
            setPanTex,
            {80, startY+gap*6, 125,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    setPanBlock.blockType = "set_pan";
    setPanBlock.hasNumberInput = true;
    setPanBlock.inputRect = {72,8,35,20};
    SoundMenuBlocks.push_back(setPanBlock);

    // clear Effects
    DraggableBlock clearBlcok = {
            clearEffectsTex,
            {80, startY+gap*7,110,40},
            false,0,0,
            false,
            -1,
            globalSoundBlockID++
    };
    clearBlcok.blockType = "clear_effects";
    SoundMenuBlocks.push_back(clearBlcok);
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
                if(handleNumberInputClick(mx,my,i))
                    return;

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
                temp.dragging = true;
                temp.offsetX = mx - temp.rect.x;
                temp.offsetY = my - temp.rect.y;
                workspaceBlocks.erase(workspaceBlocks.begin() + i);
                workspaceBlocks.push_back(temp);
                caught = true;
                return;
                for(auto& b : workspaceBlocks)
                    if(&b != &workspaceBlocks.back())
                        b.isTyping = false;
                break;
            }
        }

        if(!caught && codeTabActive && soundBtnActive) {
            for(auto& mb:SoundMenuBlocks) {
                if(isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;
                    newNode.blockType = mb.blockType;
                    newNode.id = globalSoundBlockID++;
                    newNode.parentID = -1;
                    newNode.dragging = true;

                    newNode.rect.x = mx - mb.rect.w/2;
                    newNode.rect.y = my - mb.rect.h/2;

                    newNode.dragging = true;
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
        if(wb.hasNumberInput) {
            SDL_Rect absInput = {
                    wb.rect.x + wb.inputRect.x,
                    wb.rect.y + wb.inputRect.y,
                    wb.inputRect.w,
                    wb.inputRect.h
            };

            SDL_Color textColor = wb.isTyping ? SDL_Color {0,0,255,255} : SDL_Color {0,0,0,255};
            drawTextCentered(renderer, font,wb.inputStr,absInput,textColor);
        }
        if(wb.hasDropdown) {
            wb.dropdownRect = {
                    wb.rect.x + wb.dropdownLocalRect.x,
                    wb.rect.y + wb.dropdownLocalRect.y,
                    wb.dropdownLocalRect.w,
                    wb.dropdownLocalRect.h
            };

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


// ENGINE PART

map<string, Mix_Chunk*> soundCache;

void loadSound(string name, string path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if(chunk) {
        soundCache[name] = chunk;
    }
    else {
        cout << "Failed to load sound %s!" << name.c_str() << Mix_GetError();

    }
}

void executeSoundBlock(DraggableBlock& b) {
    string effectType = "";
    if(b.hasDropdown && !b.dropdownOptions.empty())
        effectType = b.dropdownOptions[b.selectedOption];

    if(b.blockType == "play_sound") {
        string sName = b.dropdownOptions[b.selectedOption];
        if(soundCache.count(sName)) {
            Mix_Chunk* chunk = soundCache[sName];
            int ch = Mix_PlayChannel(-1,soundCache[sName], 0);
            b.activeChannel = ch;
            b.isRunning = true;
        }
        else {
            cout << "Sound not found in cache: " << endl;
        }
    }

    else if(b.blockType == "play_until_done") {
        string sName = b.dropdownOptions[b.selectedOption];
        if(soundCache.count(sName)) {
            int ch = Mix_PlayChannel(-1,soundCache[sName],0);
            b.activeChannel = ch;

            if(ch < 0) {
                cout << "Failed to play sound: " << Mix_GetError() << endl;
                b.waitingForFinish = false;
            }
            else {
                b.waitingForFinish = true;
                b.isRunning = true;
            }
        }
    }

    else if(b.blockType == "stop_all") {
        Mix_HaltChannel(-1);
    }

    else if(b.blockType == "change_pitch") {
        try {
            int v = stoi(b.inputStr);
            b.currentPitch += v;
            if(b.currentPitch > 50)
                b.currentPitch = 50;
            if(b.currentPitch < -50)
                b.currentPitch = -50;

            int newFreq = 44100 + (b.currentPitch * 200);
            //Mix_CloseAudio();
            //Mix_OpenAudio(newFreq, MIX_DEFAULT_FORMAT, 2, 2048);
        }
        catch(...) {
            cout << "Error";
        }
    }

    else if(b.blockType == "set_pitch") {
        try {
            int v = stoi(b.inputStr);
            b.currentPitch = v;
            if(b.currentPitch > 50)
                b.currentPitch = 50;
            if(b.currentPitch < -50)
                b.currentPitch = -50;

            int newFreq = 44100 + (b.currentPitch * 200);
            //Mix_CloseAudio();
            //Mix_OpenAudio(newFreq, MIX_DEFAULT_FORMAT, 2, 2048);
        }
        catch(...) {
            cout << "Error";
        }
    }

    else if(b.blockType == "change_pan") {
        try {
            int v = stoi(b.inputStr);
            if(effectType == "pan") {
                b.currentPan = v;
                if(b.currentPan > 128)
                    b.currentPan = 128;
                if(b.currentPan < -128)
                    b.currentPan = -128;

                int left = 128 - b.currentPan;
                int right = 128 + b.currentPan;

                Mix_SetPanning(-1,left,right);
            }
            else if(effectType == "pitch") {
                b.currentPitch = v;
                if(b.currentPitch > 50)
                    b.currentPitch = 50;
                if(b.currentPitch < -50)
                    b.currentPitch = -50;

                int newFreq = 44100 + (b.currentPitch * 200);
                Mix_CloseAudio();
                Mix_OpenAudio(newFreq,MIX_DEFAULT_FORMAT,2,2048);
            }
        }
        catch(...) {
            cout << "Error";
        }
    }

    else if(b.blockType == "set_pan") {
        try {
            int v = stoi(b.inputStr);
            Mix_SetPanning(-1,128-v,128+v);
        }
        catch(...) {
            cout << "Error" << endl;
        }
    }

    else if(b.blockType == "clear_effects") {
        b.currentPan = 0;
        b.currentPitch = 0;
        Mix_SetPanning(-1,128,128);

        //Mix_CloseAudio();
        //Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    }
}


#endif //INC_14041016_SOUND_H
