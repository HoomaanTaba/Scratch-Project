#ifndef SCRATCH_PROJECT_VARIABLES_H
#define SCRATCH_PROJECT_VARIABLES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;

struct Variable_Data {
    string name;
    string value;
    bool isVisible;
};

enum Variable_Block_Type {
    BLOCK_SET,
    BLOCK_CHANGE,
    BLOCK_SHOW,
    BLOCK_HIDE
};

static map<string,Variable_Data> globalVars;
static bool isNamingVariable = false;
static string newVarNameInput = "";
static SDL_Rect makeVarBtn = {85,55,150,32};
static SDL_Rect inputDialogRect = {440,300,400,130};

struct VariableRuntime {
    Variable_Block_Type type;
    string targetVar;
    string inputStr;
};

static map<int,VariableRuntime > varRuntimeData;

struct DraggableVarBlock {
    SDL_Texture* texture=nullptr;
    SDL_Rect rect = {0,0,0,0,};
    SDL_Rect inputRect = {0,0,55,22};
    bool dragging = false;
    int offsetX = 0, offsetY = 0;
    int id=-1;
    Variable_Block_Type varType;
    string targetVarName= "my variable";
    string textValue = "0";

    void updateBoxes(TTF_Font* font) {
        int tw = 0, th = 0;
        if (!textValue.empty() && font) {
            TTF_SizeText(font, textValue.c_str(), &tw, &th);
        }
        if (varType == BLOCK_SHOW || varType == BLOCK_HIDE) {
            inputRect = {rect.x+100,rect.y+10,60,22};
        }
        else {
            inputRect ={rect.x+90,rect.y+10,60,22};
        }
    }
};

static vector<DraggableVarBlock> varWorkspaceBlocks;
static vector<DraggableVarBlock> VarMenuBlocks;

inline void ExucateVariable(int blockId) {
    if (varRuntimeData.find(blockId) == varRuntimeData.end()) return;

    VariableRuntime &run=varRuntimeData[blockId];
    string target = run.targetVar;

    if (globalVars.find(target) == globalVars.end()) return;

    if (run.type == BLOCK_SET) {
        globalVars[target].value = run.inputStr;
    }
    else if (run.type == BLOCK_CHANGE) {
        try {
            double currentV = stod(globalVars[target].value);
            double changeV = stod(run.inputStr);
            double result = currentV + changeV;

            string resStr = to_string(result);
            resStr.erase(resStr.find_last_not_of("0")+1,string::npos);
            if (resStr.back() == '.') resStr.pop_back();

            globalVars[target].value = resStr;
        } catch (...) {
            globalVars[target].value += run.inputStr;
        }
    }
    else if (run.type == BLOCK_SHOW) {
        globalVars[target].isVisible = true;
    }
    else if (run.type == BLOCK_HIDE) {
        globalVars[target].isVisible = false;
    }
}
inline void CycleVariableTarget(int blockId) {
    if (globalVars.empty()) return;

    string current = varRuntimeData[blockId].targetVar;
    auto it = globalVars.find(current);

    if (it != globalVars.end()) {
        it ++ ;
        if (it == globalVars.end()) it = globalVars.begin();

        varRuntimeData[blockId].targetVar = it->first;

        for (auto &vb: varWorkspaceBlocks) {
            if (vb.id==blockId) {
                vb.targetVarName = it ->first;
                break;
            }
        }
    }
}

inline void RenderVariableMonitor(SDL_Renderer* ren,TTF_Font* font,SDL_Rect stage) {
    int xPos = stage.x + 10;
    int yPos = stage.y + 10;

    for (auto it = globalVars.begin(); it != globalVars.end(); it++) {
        if (!it ->second.isVisible) continue;

        SDL_Rect bg={xPos,yPos,140,24};
        SDL_SetRenderDrawColor(ren,220,220,220,255);
        SDL_RenderFillRect(ren,&bg);

        SDL_SetRenderDrawColor(ren,160,160,160,255);
        SDL_RenderDrawRect(ren,&bg);

        SDL_Rect valBox {xPos+90,yPos+3,45,18};
        SDL_SetRenderDrawColor(ren,255,140,26,255);
        SDL_RenderFillRect(ren,&valBox);

        yPos += 30;
    }
}
inline void SnapVariableBlocks(DraggableVarBlock& currentBlock,vector<DraggableVarBlock>& workspace) {
    for (auto& other : workspace) {
        if (currentBlock.id == other.id) continue;

        if (abs(currentBlock.rect.x - other.rect.x) < 20 && abs(currentBlock.rect.y - (other.rect.y+other.rect.h)) < 20) {
            currentBlock.rect.x = other.rect.x;
            currentBlock.rect.y = other.rect.y + other.rect.h;
            break;
        }
    }
}
#endif //SCRATCH_PROJECT_VARIABLES_H