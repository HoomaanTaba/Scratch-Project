#ifndef OPERATORUI_H
#define OPERATORUI_H


#include "UI_Objects.h"
static int globalOperatorsBlockID = 7000;
// SideButton of Operators in code menu
SideButton operatorsBtn = {
        1,
        "Operators",
        {89,192,89,255},
        {0,480,70,65},
        false
};

void initOperators(SDL_Renderer* renderer) {
    // Hat Blocks
    SDL_Texture* addTex = IMG_LoadTexture(renderer, "add.png"); //+
    SDL_Texture* subtractTex  = IMG_LoadTexture(renderer, "subtract.png"); //-
    SDL_Texture* multiplyTex  = IMG_LoadTexture(renderer, "multiply.png"); //*
    SDL_Texture* divideTex  = IMG_LoadTexture(renderer, "divide.png"); // /
    SDL_Texture* randomTex  = IMG_LoadTexture(renderer, "random.png"); // pick random num
    SDL_Texture* greater_thanTex  = IMG_LoadTexture(renderer, "greater_than.png"); // >
    SDL_Texture* lesser_thanTex=IMG_LoadTexture(renderer, "lesser_than.png"); // <
    SDL_Texture* equalTex = IMG_LoadTexture(renderer,"equal.png"); // =
    SDL_Texture* andTex = IMG_LoadTexture(renderer,"and.png"); // and
    SDL_Texture* orTex = IMG_LoadTexture(renderer,"or.png"); // or
    SDL_Texture* notTex = IMG_LoadTexture(renderer,"not.png"); // not
    SDL_Texture* joinTex = IMG_LoadTexture(renderer,"join.png"); //join
    SDL_Texture* letterTex = IMG_LoadTexture(renderer,"letter.png"); // letter of
    SDL_Texture* lengthTex = IMG_LoadTexture(renderer,"length.png"); // length of
    SDL_Texture* containTex = IMG_LoadTexture(renderer,"contain.png"); // contains
    SDL_Texture* modTex = IMG_LoadTexture(renderer,"mod.png"); // mod
    SDL_Texture* roundTex = IMG_LoadTexture(renderer,"round.png"); // round
    SDL_Texture* abs_etcTex = IMG_LoadTexture(renderer,"abs.png"); //this is a formal name beacuse this operator contains other mathematical operations too
    int startY = 93, gap = 30;

    // Math operations ( + - * /)
    OperatorMenuBlocks.push_back({
                                         addTex,
                                         {80, startY, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         subtractTex,
                                         {80, startY+gap, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         multiplyTex,
                                         {80, startY+gap*2, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         divideTex,
                                         {80, startY+gap*3, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    //pick random
    OperatorMenuBlocks.push_back({
                                         randomTex,
                                         {80, startY+gap*4, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    //logic comparisons
    OperatorMenuBlocks.push_back({
                                         greater_thanTex,
                                         {80, startY+gap*5, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         lesser_thanTex,
                                         {80, startY+gap*6, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         equalTex,
                                         {80, startY+gap*7, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    //boolean logic (and or not)
    OperatorMenuBlocks.push_back({
                                         andTex,
                                         {80, startY+gap*8, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         orTex,
                                         {80, startY+gap*9, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         notTex,
                                         {80, startY+gap*10, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    //string operations (join,letter of,length of,contains
    OperatorMenuBlocks.push_back({
                                         joinTex,
                                         {80, startY+gap*11, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         letterTex,
                                         {80, startY+gap*12, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         lengthTex,
                                         {80, startY+gap*13, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         containTex,
                                         {80, startY+gap*14, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    //advanced math
    OperatorMenuBlocks.push_back({
                                         roundTex,
                                         {80, startY+gap*15-25, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    OperatorMenuBlocks.push_back({
                                         modTex,
                                         {80, startY+gap*16-25, 75, 25},
                                         false, 0, 0,
                                         false,
                                         -1,
                                         globalOperatorsBlockID++
                                 });
    DraggableBlock absBlock = {
            abs_etcTex,
            {80, startY+gap*17-20, 75, 25},
            false, 0, 0,
            false,
            -1,
            globalOperatorsBlockID++
    };
    absBlock.hasDropdown = true;
    absBlock.dropdownOptions = {"abs","floor","ceiling","sqrt","sin","cos","tan","asin","acos","atan","ln","log","e^","10^"};
    absBlock.dropdownRect = {0,0,75,22};
    OperatorMenuBlocks.push_back(absBlock);
}

void handleOperatorBlock(SDL_Event& e, bool codeTabActive, bool operatorsBtnActive) {
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

        if(!caught && codeTabActive && operatorsBtnActive) {
            for(auto& mb:OperatorMenuBlocks) {
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

void renderOperatorBlocks(SDL_Renderer* renderer,TTF_Font * font, bool codeTabActive, bool operatorsBtnActive) {
    if(codeTabActive && operatorsBtnActive) {
        for(auto& mb : OperatorMenuBlocks) {
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


#endif //OPERATORUI_H
