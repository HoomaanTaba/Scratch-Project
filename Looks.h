//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_LOOKS_H
#define SCRATCH_LOOKS_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDLInclude.h"
#include "UI_Objects.h"
using namespace std;

static int globalLooksBlock = 3000;
SideButton looksBtn = {
    1,
    "Looks",
    {153,102,255,255},
    {0,155,70,65},
    true
};

#define BLOCK_SAY_FOR 3000
#define BLOCK_SAY 3001
#define BLOCK_THINK_FOR 3002
#define BLOCK_THINK 3003
#define BLOCK_SWITCH_COSTUME 3004
#define BLOCK_NEXT_COSTUME 3005

#define BLOCK_SHOW 3010
#define BLOCK_HIDE 3011

#define BLOCK_SWITCH_BACKDROP 3020
#define BLOCK_NEXT_BACKDROP 3021

#define BLOCK_CHANGE_SIZE 3030
#define BLOCK_SET_SIZE 3031

#define BLOCK_CHANGE_EFFECT 3040
#define BLOCK_SET_EFFECT_TO 3041
#define BLOCK_CLEAR_EFFECT 3042

#define BLOCK_GO_TO_FRONT_LAYER 3050
#define BLOCK_GO_TO_BACK_LAYER 3051
#define BLOCK_GO_FORWARD_LAYERS 3060
#define BLOCK_GO_BACKWARD_LAYERS 3061

#define BLOCK_REPORT_COSTUME_NUMBER 3101
#define BLOCK_REPORT_COSTUME_NAME 3102
#define BLOCK_REPORT_BACKDROP_NUMBER 3103
#define BLOCK_REPORT_BACKDROP_NAME 3104
#define BLOCK_REPORT_SIZE 3105


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
    SDL_Texture* goToBackTex = IMG_LoadTexture(renderer, "goToBack.png");
    SDL_Texture* goForwardLayersTex = IMG_LoadTexture(renderer, "goForwardLayers.png");
    SDL_Texture* goBackwardLayersTex = IMG_LoadTexture(renderer, "goBackwardLayers.png");
    SDL_Texture* sizeTex = IMG_LoadTexture(renderer, "size.png");
    SDL_Texture* costumeNameTex = IMG_LoadTexture(renderer, "costumeName.png");
    SDL_Texture* costumeNumberTex = IMG_LoadTexture(renderer, "costumeNumber.png");
    SDL_Texture* backdropNameTex = IMG_LoadTexture(renderer, "backdropName.png");
    SDL_Texture* backdropNumberTex = IMG_LoadTexture(renderer, "backdropNumber.png");
    int startY = 80, gap = 30;

    // sayHello for --- seconds
    DraggableBlock sayForBlock = {
        sayHelloForTex,
        {80, startY+11, 190, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    sayForBlock.hasNumberInput = false;
    sayForBlock.hasSecondNumberInput = true;
    sayForBlock.hasTextInput = true;
    sayForBlock.blockType = BLOCK_SAY_FOR;
    LooksMenuBlocks.push_back(sayForBlock);

    // sayHello
    DraggableBlock sayBlock = {
        sayHelloTex,
        {80, startY+gap*2, 80, 40},
        false, 0,0,
        false,
        -1,
        globalLooksBlock++
    };
    sayBlock.hasTextInput = true;
    sayBlock.hasNumberInput = false;
    sayBlock.blockType = BLOCK_SAY;
    LooksMenuBlocks.push_back(sayBlock);
    //think
    DraggableBlock thinkForBlock = {
        thinkTex,
        {80, startY+gap*3, 90, 45},
        false, 0, 0,
        false,
        -1,
        globalLooksBlock++
    };
    thinkForBlock.hasTextInput = true;
    thinkForBlock.hasSecondNumberInput = true;
    thinkForBlock.hasNumberInput = false;
    thinkForBlock.blockType = BLOCK_THINK_FOR;
    LooksMenuBlocks.push_back(thinkForBlock);

    DraggableBlock thinkBlock = {
        thinkTex,
        {80, startY+gap*4, 80, 40},
        false, 0,0,
        false,
        -1,
        globalLooksBlock++
    };
    thinkBlock.hasTextInput = true;
    thinkBlock.hasNumberInput = false;
    thinkBlock.blockType = BLOCK_THINK;
    LooksMenuBlocks.push_back(thinkBlock);
    // switch costume block
    DraggableBlock switchCostumeBlock = {
            switchCostumeTex,
            {80, startY+gap*5, 210, 45},
            false, 0,0,
            false,
            -1,
            globalLooksBlock++
    };
    switchCostumeBlock.blockType = BLOCK_SWITCH_COSTUME;
    switchCostumeBlock.hasDropdown = true;
    switchCostumeBlock.dropdownOptions = {"costume1", "costume2", "costume3"};
    switchCostumeBlock.dropdownRect = {0,0,100,22};
    LooksMenuBlocks.push_back(switchCostumeBlock);


    // next costume
    DraggableBlock nextCostumeBlock = {
        nextCostumeTex,
        {80, startY+gap*6, 100, 45},
        false, 0,0,
        false,
        -1,
        globalLooksBlock++
    };
    nextCostumeBlock.blockType = BLOCK_NEXT_COSTUME;
    LooksMenuBlocks.push_back(nextCostumeBlock);

    DraggableBlock switchBackdropBlock = {
            switchBackdropTex,
            {80, startY+gap*7, 220, 45},
            false,0,0,
            false,
            -1,
            globalLooksBlock++
    };
    switchBackdropBlock.blockType = BLOCK_SWITCH_BACKDROP;
    switchBackdropBlock.hasDropdown = true;
    switchBackdropBlock.dropdownOptions = {"backdrop1", "backdrop2"};
    switchBackdropBlock.dropdownRect = {0,0,100,22};
    LooksMenuBlocks.push_back(switchBackdropBlock);

    // next backdrop
    DraggableBlock nextBackdropBlock = {
        nextBackdropTex,
        {80, startY+gap*8, 100, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    nextBackdropBlock.blockType = BLOCK_NEXT_BACKDROP;
    LooksMenuBlocks.push_back(nextBackdropBlock);
    // change size by
    DraggableBlock changeSizeBlock = {
        changeSizeTex,
        {80,startY+gap*9, 170, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    changeSizeBlock.hasNumberInput = true;
    changeSizeBlock.blockType = BLOCK_CHANGE_SIZE;
    LooksMenuBlocks.push_back(changeSizeBlock);

    // set size to
    DraggableBlock setSizeBlock = {
        setSizeTex,
        {80,startY+gap*10, 160, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    setSizeBlock.hasNumberInput = true;
    setSizeBlock.blockType = BLOCK_SET_SIZE;
    LooksMenuBlocks.push_back(setSizeBlock);

    // change color effect
    DraggableBlock changeEffectBlock;
    changeEffectBlock.texture = changeColorTex;
    changeEffectBlock.rect = {80,startY+gap*11,200,45};
    changeEffectBlock.isHat = false;
    changeEffectBlock.id = globalLooksBlock++;
    changeEffectBlock.blockType = BLOCK_CHANGE_EFFECT;
    changeEffectBlock.hasDropdown = true;
    changeEffectBlock.dropdownOptions = {"color", "fisheye", "whirl", "pixelate", "mosaic", "brightness", "ghost"};
    changeEffectBlock.hasNumberInput = true;
    changeEffectBlock.inputValue = 25;
    LooksMenuBlocks.push_back(changeEffectBlock);

    // set color effect
    DraggableBlock setEffectBlock;

    setEffectBlock.texture = setColorTex;
    setEffectBlock.rect = {80, startY+gap*12, 190, 45};
    setEffectBlock.isHat = false;
    setEffectBlock.id = globalLooksBlock++;
    setEffectBlock.blockType = BLOCK_SET_EFFECT_TO;
    setEffectBlock.hasDropdown = true;
    setEffectBlock.dropdownOptions = {"color", "fisheye", "whirl", "pixelate", "mosaic", "brightness", "ghost"};
    setEffectBlock.hasNumberInput = true;
    setEffectBlock.inputValue = 0;
    LooksMenuBlocks.push_back(setEffectBlock);

    // clear graphic effects
    DraggableBlock clearGraphicEffectsBlock = {
        clearGraphicTex,
        {80, startY+gap*13, 190, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    clearGraphicEffectsBlock.blockType = BLOCK_CLEAR_EFFECT;
    LooksMenuBlocks.push_back(clearGraphicEffectsBlock);

    // show
    DraggableBlock showBlock;
    showBlock.blockType = BLOCK_SHOW;
    showBlock.texture = showTex;
    showBlock.rect = {80, startY+gap*14-22, 50, 45};
    showBlock.id = globalLooksBlock++;
    showBlock.isHat = false;
    LooksMenuBlocks.push_back(showBlock);

    // hide
    DraggableBlock hideBlock;
    hideBlock.blockType = BLOCK_SHOW;
    hideBlock.texture = hideTex;
    hideBlock.rect = {80, startY+gap*15-22, 50, 45};
    hideBlock.id = globalLooksBlock++;
    hideBlock.isHat = false;
    LooksMenuBlocks.push_back(hideBlock);

    // go to front layer
    DraggableBlock goToFrontLayerBlock{
        goToFrontTex,
        {80, startY+gap*16-22, 180, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    goToFrontLayerBlock.blockType = BLOCK_GO_TO_FRONT_LAYER;
    LooksMenuBlocks.push_back(goToFrontLayerBlock);

    DraggableBlock goToBackLayerBlock{
        goToBackTex,
        {80, startY+gap*17-22, 180, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    goToBackLayerBlock.blockType = BLOCK_GO_TO_BACK_LAYER;
    LooksMenuBlocks.push_back(goToBackLayerBlock);

    // go forward layers

    DraggableBlock goForwardLayersBlock = {
        goForwardLayersTex,
        {80, startY+gap*18-22, 200, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    goForwardLayersBlock.hasNumberInput = true;
    goForwardLayersBlock.blockType = BLOCK_GO_FORWARD_LAYERS;
    LooksMenuBlocks.push_back(goForwardLayersBlock);

    //go backward layers
    DraggableBlock goBackwardLayersBlock = {
        goBackwardLayersTex,
        {80, startY+gap*19-22, 200, 45},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    goBackwardLayersBlock.hasNumberInput = true;
    goBackwardLayersBlock.blockType = BLOCK_GO_BACKWARD_LAYERS;
    LooksMenuBlocks.push_back(goBackwardLayersBlock );

    DraggableBlock costumeNumberBlock = {
        costumeNumberTex,
{80, startY+gap*20-22, 140, 33},
        false,0,0,
        false,
        -1,
        globalLooksBlock++
    };
    costumeNumberBlock.blockType = BLOCK_REPORT_COSTUME_NUMBER;
    LooksMenuBlocks.push_back(costumeNumberBlock);

    DraggableBlock costumeNameBlock = {
        costumeNameTex,
{80, startY+gap*21-22, 140, 33},
false,0,0,
false,
-1,
globalLooksBlock++
    };
    costumeNameBlock.blockType = BLOCK_REPORT_COSTUME_NAME;
    LooksMenuBlocks.push_back(costumeNameBlock);

    DraggableBlock backdropNumberBlock = {
        backdropNumberTex,
{80, startY+gap*22-22, 140, 33},
false,0,0,
false,
-1,
globalLooksBlock++
    };
    backdropNumberBlock.blockType = BLOCK_REPORT_BACKDROP_NUMBER;
    LooksMenuBlocks.push_back(backdropNumberBlock);

    DraggableBlock backdropNameBlock = {
        backdropNameTex,
{80, startY+gap*23-22, 140, 33},
false,0,0,
  false,
-1,
     globalLooksBlock++
    };
    backdropNameBlock.blockType = BLOCK_REPORT_BACKDROP_NAME;
    LooksMenuBlocks.push_back(backdropNameBlock);

    DraggableBlock sizeBlock = {
        sizeTex,
{80, startY+gap*24-22, 50, 33},
false,0,0,
false,
-1,
globalLooksBlock++
    };
    sizeBlock.blockType = BLOCK_REPORT_SIZE;
    LooksMenuBlocks.push_back(sizeBlock);
}

void handleLooksBlock(SDL_Event& e, bool codeTabActive, bool looksBtnActive) {
    if(!codeTabActive || !looksBtnActive)
        return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {

        for (auto& b : workspaceBlocks) {
            if ((b.hasNumberInput || b.hasTextInput) && isInside(mx, my, b.inputRect1)) {
                b.editingInput1 = true;
                b.editingInput2 = false;
                SDL_StartTextInput();
                return;
            }

            if (b.hasSecondNumberInput && isInside(mx, my, b.inputRect2)) {
                b.editingInput1 = false;
                b.editingInput2 = true;
                SDL_StartTextInput();
                return;
            }
        }



        mx = e.button.x;
        my = e.button.y;
        for (auto& b : workspaceBlocks) {
            if (b.hasDropdown) {
                // click on the box
                if (isInside(mx, my, b.dropdownRect)) {
                    b.dropdownOpen = !b.dropdownOpen;
                    return;
                }
                //check options if dropdown is open
                if (b.dropdownOpen) {
                    for (int i = 0; i < b.dropdownOptions.size(); i++) {
                        SDL_Rect optionRect = {
                            b.dropdownRect.x,
                            b.dropdownRect.y + (i+1)*b.dropdownRect.h,
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

        if(!caught && codeTabActive && looksBtnActive) {
            for(auto& mb:LooksMenuBlocks) {
                if(isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;
                    if (newNode.hasDropdown) {
                        newNode.dropdownRect.x = newNode.rect.x + newNode.rect.w - 110;
                        newNode.dropdownRect.y = newNode.rect.y + 10;
                    }

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
                if (workspaceBlocks[i].hasDropdown) {
                    workspaceBlocks[i].dropdownRect.x = workspaceBlocks[i].rect.x + workspaceBlocks[i].rect.w - 110;

                    workspaceBlocks[i].dropdownRect.y = workspaceBlocks[i].rect.y + 10;
                }

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
        if (wb.hasNumberInput || wb.hasTextInput) {
            wb.inputRect1 = {
                wb.rect.x + wb.rect.w - 60,
                wb.rect.y + 12,
                50,
                20
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &wb.inputRect1);

            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderDrawRect(renderer, &wb.inputRect1);

            SDL_Color textColor = {0,0,0,255};

            string displayText;

            if (wb.hasTextInput)
                displayText = wb.inputText1;
            else {
                if (!wb.inputText1.empty())
                    displayText = wb.inputText1;
                else
                    displayText = to_string((int)wb.inputValue);
            }

            drawTextCentered(renderer, font, displayText, wb.inputRect1, textColor);

            if (wb.hasSecondNumberInput) {
                wb.inputRect2 = {
                    wb.rect.x + wb.rect.w - 60,
                    wb.rect.y + 35,
                    50,
                    20
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &wb.inputRect2);

                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                SDL_RenderDrawRect(renderer, &wb.inputRect2);

                SDL_Color textColor2 = {0, 0, 0, 255};

                string displayText2;

                if (!wb.inputText2.empty())
                    displayText2 = wb.inputText2;
                else
                    displayText2 = to_string((int)wb.inputValue2);

                drawTextCentered(renderer, font, displayText2, wb.inputRect2, textColor2);
            }
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

void renderStage(SDL_Renderer* renderer, Stage& stage) {
    if (!stage.backdrops.empty()) {
        SDL_RenderCopy(renderer, stage.backdrops[stage.currentBackdrop], NULL, NULL);
    }

    for (auto s : stage.sprites) {
        if (!s->visible)
            continue;

        SDL_Rect dst = s->rect;
        dst.w = s->rect.w * (s->size / 100.0);
        dst.h = s->rect.h * (s->size / 100.0);

        SDL_RenderCopy (renderer,
            s->costume.empty() ? s->texture : s->costume[s->currentCostume],
            NULL,
            &dst);
    }
}

void switch_backdrop_to(Stage& stage, int index) {
    if (index >= 0 && index < stage.backdrops.size())
        stage.currentBackdrop = index;
}

void next_backdrop(Stage& stage) {
    if (stage.backdrops.empty())
        return;
    stage.currentBackdrop = (stage.currentBackdrop + 1) % stage.backdrops.size();
}

void go_to_front(Sprite& s, vector<Sprite*>& sprites) {
    sprites.erase(remove(sprites.begin(), sprites.end(), &s), sprites.end());
    sprites.push_back(&s);
}

void go_to_back(Sprite& s, vector<Sprite*>& sprites) {
    sprites.erase(remove(sprites.begin(), sprites.end(), &s), sprites.end());
    sprites.insert(sprites.begin(), &s);
}

void go_forward_layers(Sprite& s, vector<Sprite*>& sprites, int layers) {
    auto it = find(sprites.begin(), sprites.end(), &s);
    if (it == sprites.end())
        return;
    int index = it - sprites.begin();
    int newIndex = min((int)sprites.size() - 1, index + layers);
    sprites.erase(it);
    sprites.insert(sprites.begin() + newIndex, &s);
}

void go_backward_layers(Sprite& s, vector<Sprite*>& sprites, int layers) {
    auto it = find(sprites.begin(), sprites.end(), &s);
    if (it == sprites.end())
        return;
    int index = it - sprites.begin();
    int newIndex = max(0, index - layers);
    sprites.erase(it);
    sprites.insert(sprites.begin() + newIndex, &s);
}

void change_effect(Sprite& s, string effect, double value) {
    s.effects[effect] += value;
}

void set_effect(Sprite& s, string effect, double value) {
    s.effects[effect] = value;
}

void clear_graphic_effects(Sprite& s) {
    s.effects.clear();
}

int get_costume_number(Sprite& s) {
    return s.currentCostume + 1;
}

string get_costume_name(Sprite& s) {
    return s.costumeNames[s.currentCostume];
}

int get_backdrop_number(Stage& stage) {
    return stage.currentBackdrop + 1;
}

string get_backdrop_name(Stage& stage) {
    return stage.backdropNames[stage.currentBackdrop];
}

int get_size(Sprite& s) {
    return s.size;
}

void show (Sprite& s) {
    s.visible = true;
}

void hide (Sprite& s) {
    s.visible = false;
}

void switch_costume_to (Sprite& s, int index) {
    if (index >= 0 && index < s.costume.size())
        s.currentCostume = index;
}

void next_costume (Sprite& s, int totalCostumes) {
    if (s.costume.size() == 0)
        return;

    s.currentCostume = (s.currentCostume + 1) % s.costume.size();
}

void change_size_by (Sprite& s, double amount) {
    s.size += amount;

    if (s.size > 540) {
        s.size = 540;
    }

    if (s.size < 5) {
        s.size = 5;
    }
}

void set_size (Sprite& s, double percentage) {
    s.size = percentage;

    if (s.size > 540) {
        s.size = 540;
    }

    if (s.size < 5) {
        s.size = 5;
    }
}

void say (Sprite& s, string text) {
    s.message = text;
    s.messageType = 1;

    s.messageDuration = 0;
}

void think (Sprite& s, string text) {
    s.message = text;
    s.messageType = 2;

    s.messageDuration = 0;
}

void say_for_seconds (Sprite& s, string text, int time) {
    s.message = text;
    s.messageType = 1;

    s.messageStartTime = SDL_GetTicks();
    s.messageDuration = time*1000;
}

void think_for_seconds (Sprite& s, string text, int time) {
    s.message = text;
    s.messageType = 2;

    s.messageStartTime = SDL_GetTicks();
    s.messageDuration = time*1000;
}

void update_message(Sprite& s) {
    if (s.messageDuration > 0) {
        Uint32 now = SDL_GetTicks();

        if (now - s.messageStartTime > s.messageDuration) {
            s.message = "";
            s.messageType = 0;
            s.messageDuration = 0;
        }
    }
}

void render_message (Sprite& s, SDL_Renderer* renderer, TTF_Font* font) {
    if (s.messageType == 0 || s.message.empty())
        return;

    SDL_Color textColor = {40, 40, 40, 255};

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, s.message.c_str(), textColor);
    if (!textSurface)
        return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }

    int textW = textSurface->w;
    int textH = textSurface->h;

    int padding = 20;

    int bubbleW = textW + padding;
    int bubbleH = textH + padding;

    int centerX = s.rect.x + s.rect.w / 2;
    int bubbleX = centerX - bubbleW / 2;
    int bubbleY = s.rect.y - bubbleH - 30;


    if (s.messageType == 1) {
        roundedBoxRGBA(
            renderer,
            bubbleX,
            bubbleY,
            bubbleW + bubbleX,
            bubbleH + bubbleY,
            18,
            255,255,255,255
            );

        roundedRectangleRGBA(
            renderer,
            bubbleX,
            bubbleY,
            bubbleW + bubbleX,
            bubbleH + bubbleY,
            18,
            180,180,180,255
            );

        Sint16 vx[3] = {
            (Sint16)(centerX - 10),
            (Sint16)(centerX + 10),
            (Sint16)(centerX)
        };

        Sint16 vy[3] = {
            (Sint16)(bubbleY + bubbleH),
            (Sint16)(bubbleY + bubbleH),
            (Sint16)(bubbleY + bubbleH + 15)
        };

        filledPolygonRGBA(renderer, vx, vy, 3, 255, 255, 255, 255);
        polygonRGBA(renderer, vx, vy, 3, 180, 180, 180, 255);
    }
    if (s.messageType == 2) {

        int ellipseCenterY = bubbleY + bubbleH / 2;

        filledEllipseRGBA(
        renderer,
        centerX,
        ellipseCenterY,
        bubbleW/2,
        bubbleH/2,
        255,255,255,255);

        ellipseRGBA(renderer,
            centerX,
            ellipseCenterY,
          bubbleW/2,
        bubbleH/2,
            180, 180, 180, 255);

        int mediumX = centerX - bubbleW / 4;
        int mediumY = bubbleY + bubbleH + 10;

        filledCircleRGBA(renderer,
            mediumX,
            mediumY,
            8,
            255, 255, 255, 255);

        circleRGBA(renderer,
            mediumX,
            mediumY,
            8,
            180, 180, 180, 255);

        int smallX = centerX - bubbleW / 6;
        int smallY = mediumY + 18;

        filledCircleRGBA(renderer,
            smallX,
            smallY,
            5,
            255, 255, 255, 255);

        circleRGBA(renderer,
            smallX,
            smallY,
            5,
            180, 180, 180, 255);
        }

    SDL_Rect textRect;
    textRect.w = textW;
    textRect.h = textH;
    textRect.x = bubbleX + (bubbleW - textW) / 2;
    textRect.y = bubbleY + (bubbleH - textH) / 2;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

#endif //SCRATCH_LOOKS_H