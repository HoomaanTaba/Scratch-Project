#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

using namespace std;

#include "Operator.h"
#include "Variables.h"
#include "ControlOrders.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Rect topBar = {0,0,SCREEN_WIDTH,45};
SDL_Rect categoryBar = {0, 45, 75, 675};
SDL_Rect blocksPalette = {75, 45, 250, 675};
SDL_Rect stageRect = {850, 60, 410, 320};

enum BlockCategory {CAT_MOTION, CAT_LOOKS, CAT_SOUND, CAT_EVENTS, CAT_CONTROL, CAT_SENSING, CAT_OPERATORS, CAT_VARIABLES, CAT_NONE};
BlockCategory currentCategory = CAT_OPERATORS;

struct Category {
    string name;
    SDL_Color color;
    BlockCategory type;
};
static bool isMathMenuOpen = false;
static int mathMenuTargetID= -1;
static SDL_Rect mathMenuRect = {0, 0, 100 , 200};

vector<Category> categories = {
    {"Motion",{76,151,255,255}, CAT_MOTION},
    {"Looks",{153,101,255,255}, CAT_LOOKS},
    {"Sound",{214,92,215,255}, CAT_SOUND},
    {"Events",{255,213,65,255}, CAT_EVENTS},
    {"Contro",{255,171,25,255}, CAT_CONTROL},
    {"Sensing",{76,191,230,255}, CAT_SENSING},
    {"Operators",{89,191,85,255}, CAT_OPERATORS},
    {"Variables",{255,140,26,255}, CAT_VARIABLES},
};

int focusedType = 0;

void FillCircle(SDL_Renderer* ren,int cx, int cy, int r) {
    for (double dy=1; dy<=r; dy+= 1.0) {
        double dx = floor(sqrt(2.0*r*dy- (dy*dy)));
        SDL_RenderDrawLine(ren,cx-dx,cy+r-dy,cx+dx,cy+r-dy);
        SDL_RenderDrawLine(ren,cx-dx,cy-r+dy,cx+dx,cy-r+dy);
    }
}

void renderText(SDL_Renderer* ren,TTF_Font* font,string txt,int x, int y, SDL_Color col = {0,0,0,255}) {
    if (txt.empty() || ! font) return;
    SDL_Surface* s=TTF_RenderUTF8_Blended(font, txt.c_str(), col);
    if (!s) return;
    SDL_Texture* t = SDL_CreateTextureFromSurface(ren, s);
    SDL_Rect r = {x, y, s->w, s->h};
    SDL_RenderCopy(ren, t, NULL, &r);
    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
};
bool isVarMenuOpen = false;
int varMenuTargetID= -1;
SDL_Rect varMenuRect = {0, 0, 150,0};

const char* ctrlFiles[]={"wait.png", "repeat.png", "forever.png", "if.png", "if_else.png", "stop.png"};
Control_Block_Type cTypes[]={BLOCK_WAIT, BLOCK_REPEAT, BLOCK_FOREVER, BLOCK_IF, BLOCK_IF_ELSE, BLOCK_STOP_ALL};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* win = SDL_CreateWindow("Scratch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    globalFont=TTF_OpenFont("arial.ttf", 13);
    globalVars["my variable"] = {"my variable", "0", true};

    const char* imgFiles[]= {"add.png", "subtract.png", "multiply.png", "divide.png", "random.png", "greater_than.png", "lesser_than.png", "equal.png", "and.png", "or.png", "not.png", "join.png", "letter.png", "length.png", "contain.png", "mod.png", "round.png", "abs.png" };
    Operator_Block_Type oTypes[]={BLOCK_ADD, BLOCK_SUBTRACT, BLOCK_MULTIPLY, BLOCK_DIVIDE, BLOCK_RANDOM, BLOCK_GREATER_THAN, BLOCK_LESS_THAN, BLOCK_EQUAL, BLOCK_AND, BLOCK_OR, BLOCK_NOT, BLOCK_JOIN, BLOCK_LETTER_OF, BLOCK_LENGTH, BLOCK_CONTAINS, BLOCK_MOD, BLOCK_ROUND, BLOCK_ABS };

    for ( int i=0;i<18;i++) {
        DraggableBlock b;
        b.texture = IMG_LoadTexture(ren, imgFiles[i]);
        if (b.texture) {
            int w,h; SDL_QueryTexture(b.texture, NULL, NULL, &w, &h);
            b.rect = {90, 70 + (i*36), (int)(w*0.45f), (int)(h*0.45f)};
        }
        b.opType = oTypes[i];
        b.hasSecondNumber = (b.opType != BLOCK_NOT && b.opType != BLOCK_LENGTH && b.opType != BLOCK_ROUND && b.opType != BLOCK_ABS);
        OperatorMenuBlocks.push_back(b);
    }

    for (int i=0;i<6;i++) {
        DraggableControl b;
        b.texture = IMG_LoadTexture(ren, ctrlFiles[i]);
        if (b.texture) {
            int w,h; SDL_QueryTexture(b.texture, NULL, NULL, &w, &h);
            b.rect = {90,70+(i*115), (int)(w*0.45f), (int)(h*0.45f)};
        }
        b.type = cTypes[i];
        b.id = globalCtrlID++;
        controlMenu.push_back(b);
    }

    const char* varFiles[] = {"set.png", "change.png", "show.png", "hide.png"};
    Variable_Block_Type vTypes[]={BLOCK_SET, BLOCK_CHANGE, BLOCK_SHOW, BLOCK_HIDE};
    for (int i=0;i<4;i++) {
        DraggableVarBlock v;
        v.texture = IMG_LoadTexture(ren, varFiles[i]);
        if (v.texture) {
            int w,h; SDL_QueryTexture(v.texture, NULL, NULL, &w, &h);
            v.rect = {90,100+(i*45), (int)(w*0.45f), (int)(h*0.45f)};
        }
        v.varType = vTypes[i];
        VarMenuBlocks.push_back(v);
    }

    SDL_Texture* catSprite = IMG_LoadTexture(ren, "cat.png");
    SDL_Rect catPos = {stageRect.x+150,stageRect.y +110, 100, 100};

    bool run = true; SDL_Event e;
    while (run) {
        int mx,my; SDL_GetMouseState(&mx,&my);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) run = false;

            HandleControlEvents(e,mx,my);

            if (isNamingVariable) {
                if (e.type == SDL_TEXTINPUT) {
                    newVarNameInput += e.text.text;
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        if (!newVarNameInput.empty()) globalVars[newVarNameInput] = {newVarNameInput, "0", true};
                        isNamingVariable = false; SDL_StopTextInput();
                    } else if (e.key.keysym.sym == SDLK_BACKSPACE && !newVarNameInput.empty()) {
                        newVarNameInput.pop_back();
                    }
                    else if (e.key.keysym.sym == SDLK_ESCAPE) {
                        isNamingVariable = false; SDL_StopTextInput();
                    }
                }
                continue;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                bool hit = false;
                if (isInside(mx,my,categoryBar)) {
                    int idx= (my-45)/70;
                    if (idx>=0 && idx<(int)categories.size()) { currentCategory = categories[idx].type; hit = true; }
                }

                if (!hit && currentCategory == CAT_VARIABLES && isInside(mx,my,makeVarBtn)) {
                    isNamingVariable = true; newVarNameInput = ""; SDL_StartTextInput(); hit = true;
                }
                for (int i = (int)workspaceBlocks.size()-1; i>=0; i--) {
                    auto& b = workspaceBlocks[i];
                    if (isInside(mx,my,b.boxA)) {focusedBlockID = b.id; focusedField = 1; focusedType = 1;SDL_StartTextInput(); hit = true; break; }
                    if (b.hasSecondNumber && isInside(mx,my, b.boxB)){ focusedBlockID = b.id; focusedField = 2; focusedType = 1; SDL_StartTextInput(); hit = true; break;  }
                    if (isInside(mx,my,b.rect)) {EvaluateOperator(b.id);b.dragging = true; b.offsetX = mx-b.rect.x;b.offsetY = my-b.rect.y;hit = true; break; }
                    if (isInside(mx,my,b.rect) && b.opType == BLOCK_ABS) {
                        if (mx < b.rect.x + 60) {
                            isMathMenuOpen = !isMathMenuOpen;
                            mathMenuTargetID = b.id;
                            mathMenuRect = {mx,my,80,(int)mathFunctions.size()*20};
                            hit = true;
                        }
                    }
                    if (!hit && isMathMenuOpen && isInside(mx,my,mathMenuRect)) {
                        int selection = (my-mathMenuRect.y)/20;
                        if (selection >= 0 && selection < mathFunctions.size()) {
                            operatorRuntimeData[mathMenuTargetID].mathFuncIndex = selection;
                            EvaluateOperator(mathMenuTargetID);
                        }
                        isMathMenuOpen = false;
                        hit = true;
                    }
                }
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    for (auto& v:varWorkspaceBlocks) {
                        if (isInside(mx,my,v.rect)) {
                            auto it = globalVars.find(v.targetVarName);
                            if (it!=globalVars.end()) {
                                it ++;
                                if (it == globalVars.end()) it = globalVars.begin();

                                v.targetVarName = it ->first;
                                varRuntimeData[v.id].targetVar = it ->first;
                                v.updateBoxes(globalFont);
                            }
                            hit = true;
                            break;
                        }
                    }
                }

                if (!hit) {
                    for (int i = (int)varWorkspaceBlocks.size()-1; i>=0; i--) {
                        auto& v= varWorkspaceBlocks[i];
                        if (isInside(mx,my,v.inputRect) && (v.varType ==BLOCK_SET || v.varType == BLOCK_CHANGE)) {focusedBlockID = v.id;focusedType = 2; SDL_StartTextInput(); hit = true; break; }
                        if (isInside(mx,my,v.rect)) {v.dragging = true; v.offsetX = mx-v.rect.x;v.offsetY = my-v.rect.y;ExucateVariable(v.id);hit = true; break; }

                    }
                }
                if (!hit && isInside(mx,my, blocksPalette)) {
                    if (currentCategory == CAT_OPERATORS) {
                        for (auto& mb: OperatorMenuBlocks) if (isInside(mx,my,mb.rect)) {
                            DraggableBlock n=mb; n.id = globalBlockID++;
                            n.rect.x = mx-20; n.rect.y = my-10; n.dragging = true; n.offsetX = 20; n.offsetY  = 10;
                            operatorRuntimeData[n.id].type = n.opType; n.updateBoxes(globalFont); workspaceBlocks.push_back(n); hit = true; break;
                        }
                    } else if (currentCategory == CAT_VARIABLES) {
                        for (auto& mv: VarMenuBlocks) if (isInside(mx,my,mv.rect)) {
                            DraggableVarBlock n=mv; n.id = globalBlockID++;
                            n.rect.x = mx-20; n.rect.y = my-10;n.dragging = true; n.offsetX = 20; n.offsetY  = 10;
                            varRuntimeData[n.id].type = n.varType;
                            if (!globalVars.empty()) {
                                n.targetVarName = globalVars.begin() -> first;
                                varRuntimeData[n.id].targetVar = n.targetVarName;
                            }else {
                                n.targetVarName = "my Variable";
                                varRuntimeData[n.id].targetVar = "my Variable";
                            }
                            n.updateBoxes(globalFont); varWorkspaceBlocks.push_back(n);hit = true; break;
                        }
                    }else if (currentCategory == CAT_CONTROL) {
                        for (auto& mc : controlMenu) if (isInside(mx,my,mc.rect)) {
                            DraggableControl n=mc; n.id = globalBlockID++;
                            n.rect.x = mx-20; n.rect.y = my-10; n.dragging = true;
                            controlWorkspace.push_back(n); hit = true; break;
                        }
                    }
                }
                if (!hit) {focusedBlockID = -1; focusedType = 0;SDL_StopTextInput();}
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                for (auto& b:workspaceBlocks) b.dragging = false;
                for (auto& v : varWorkspaceBlocks) { v.dragging = false; SnapVariableBlocks(v,varWorkspaceBlocks);}
            }

            if (e.type == SDL_TEXTINPUT && focusedBlockID != -1) {
                if (focusedType == 1) {
                    for (auto& b:workspaceBlocks) if (b.id == focusedBlockID) {
                        if (focusedField == 1) b.textA += e.text.text; else b.textB += e.text.text;
                        operatorRuntimeData[b.id].strA = b.textA; operatorRuntimeData[b.id].strB = b.textB;
                        EvaluateOperator(b.id); b.updateBoxes(globalFont);
                    }
                } else if (focusedType == 2) {
                    for (auto& v: varWorkspaceBlocks) if (v.id == focusedBlockID) {
                        v.textValue += e.text.text; varRuntimeData[v.id].inputStr = v.textValue; v.updateBoxes(globalFont);
                    }
                }
            }
        }

        for (auto& b: workspaceBlocks) if (b.dragging) {b.rect.x = mx - b.offsetX; b.rect.y = my - b.offsetY;b.updateBoxes(globalFont);}
        for (auto& v : varWorkspaceBlocks) if (v.dragging) {v.rect.x = mx -v.offsetX;v.rect.y = my -v.offsetY;v.updateBoxes(globalFont);}


        SDL_SetRenderDrawColor(ren, 235, 235, 235, 255); SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 77, 151, 235, 255); SDL_RenderFillRect(ren,&topBar);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); SDL_RenderFillRect(ren, &categoryBar);

        for (int i = 0;i<(int)categories.size();i++) {
            SDL_SetRenderDrawColor(ren,categories[i].color.r,categories[i].color.g,categories[i].color.b,255);
            FillCircle(ren,37,80+(i*70),15);
        }
        SDL_SetRenderDrawColor(ren, 249, 249, 249, 255); SDL_RenderFillRect(ren,&blocksPalette);

        if (currentCategory == CAT_OPERATORS) {
            for (auto&mb : OperatorMenuBlocks) SDL_RenderCopy ( ren, mb.texture, NULL, &mb.rect);
        } else if ( currentCategory == CAT_VARIABLES) {
            SDL_SetRenderDrawColor(ren, 255, 149, 26, 255); SDL_RenderFillRect(ren, &makeVarBtn);
            renderText(ren,globalFont,"Make a Variable",makeVarBtn.x+40,makeVarBtn.y+7,{255,255,255,255});
            int listY=100;

            for (auto it = globalVars.begin();it != globalVars.end();it++) {
                const string& name = it -> first;
                renderText(ren,globalFont,"Var:" +name , 95,listY,{0,0,0,255});
                listY+=25;
            }
            for (auto& mv: VarMenuBlocks) {mv.rect.y = listY + 10 ; SDL_RenderCopy(ren,mv.texture,NULL,&mv.rect); listY+=45;}
        } else if (currentCategory == CAT_CONTROL) {
            for (auto& mc: controlMenu) SDL_RenderCopy ( ren, mc.texture, NULL, &mc.rect);
        }

        SDL_SetRenderDrawColor(ren,255,255,255,255); SDL_RenderFillRect(ren,&stageRect);
        if (catSprite) SDL_RenderCopy(ren,catSprite,NULL,&catPos);

        RenderVariableMonitor(ren,globalFont,stageRect);

        int mY = stageRect.y + 14;
        for (auto it = globalVars.begin();it != globalVars.end();it++) {
            const string& name = it -> first;
            auto& var = it ->second;
            if (!var.isVisible) continue;

            renderText(ren, globalFont, name+":",stageRect.x+15,mY,{0,0,0,255});
            SDL_Rect valueBox = {stageRect.x+120,mY-2,50,20};
            SDL_SetRenderDrawColor(ren,250,149,25,255);
            SDL_RenderFillRect(ren,&valueBox);
            renderText(ren, globalFont, var.value,stageRect.x+15,mY,{255,255,255,255});
            mY+=30;
        }
        for (auto& wb : workspaceBlocks) {
            SDL_RenderCopy(ren, wb.texture, NULL, &wb.rect);
            SDL_SetRenderDrawColor(ren,255,255,255,255);
            SDL_RenderFillRect(ren,&wb.boxA);
            renderText(ren,globalFont,wb.textA,wb.boxA.x+5,wb.boxA.y+4);
            if (wb.hasSecondNumber) {
                SDL_RenderFillRect(ren,&wb.boxB); renderText(ren,globalFont,wb.textB,wb.boxB.x + 5, wb.boxB.y +4);
                renderText(ren,globalFont,wb.textB, wb.boxB.x + 5, wb.boxB.y + 3);
            }
            if (operatorRuntimeData[wb.id].showResult) {
                string res = operatorRuntimeData[wb.id].result;
                int bubbleX=wb.rect.x;
                if (focusedBlockID == wb.id) {
                    bubbleX = (focusedBlockID == 1) ? wb.boxA.x : wb.boxB.x;
                } else {
                    bubbleX = wb.rect.x + (wb.rect.w/2) -15;
                }
                SDL_Rect bubble = {wb.rect.x +10 , wb.rect.y -25, (int)res.length()*8 + 20, 22};
                SDL_SetRenderDrawColor(ren,255,255,200,255); SDL_RenderFillRect(ren,&bubble);
                renderText(ren,globalFont,res,bubble.x+5,bubble.y+4,{0,0,0,255});
            }
        }
        for (auto& vb : varWorkspaceBlocks) {
            SDL_RenderCopy(ren, vb.texture, NULL, &vb.rect);
            renderText(ren,globalFont,vb.targetVarName,vb.rect.x+45,vb.rect.y+12,{255,255,255,255});
            if (vb.varType == BLOCK_SET || vb.varType == BLOCK_CHANGE) {
                SDL_SetRenderDrawColor(ren,255,255,255,255); SDL_RenderFillRect(ren,&vb.inputRect);
                renderText(ren,globalFont,vb.textValue,vb.inputRect.x+8,vb.inputRect.y+4);
            }
        }
        RenderControlSystem(ren);

        if (isNamingVariable) {
            SDL_SetRenderDrawColor(ren,255,255,255,255); SDL_RenderFillRect(ren,&inputDialogRect);
            renderText(ren,globalFont,"Variable Name: ",inputDialogRect.x+20,inputDialogRect.y+20);
            renderText(ren,globalFont,newVarNameInput + "|",inputDialogRect.x+20, inputDialogRect.y+50);
        }
        if (isMathMenuOpen) {
            SDL_SetRenderDrawColor(ren,255,255,255,255); SDL_RenderFillRect(ren,&inputDialogRect);
            SDL_RenderFillRect(ren,&mathMenuRect);
            SDL_SetRenderDrawColor(ren,200,200,200,255);
            SDL_RenderDrawRect(ren,&mathMenuRect);

            for (int i =0;i<mathFunctions.size();i++) {
                SDL_Rect itemRect = {mathMenuRect.x,mathMenuRect.y+(i*20),mathMenuRect.w,20};
                if (mx>=itemRect.x && mx<itemRect.x+itemRect.w && my>=itemRect.y && my<itemRect.y+itemRect.h) {
                    SDL_SetRenderDrawColor(ren,74,144,225,255);
                    SDL_RenderFillRect(ren,&itemRect);
                }
                renderText(ren,globalFont,mathFunctions[i],itemRect.x+5,itemRect.y+2,{0,0,0,255});
            }
        }
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    TTF_CloseFont(globalFont); SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
    TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}


#ifndef SCRATCH_PROJECT_CONTROLORDERS_H
#define SCRATCH_PROJECT_CONTROLORDERS_H
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;
struct ExecationContext {
    bool isRunning = true;
    bool stopAll = false;
    int watchdogCounter = 0;
};

typedef void(*CommandFn)(ExecationContext&);
typedef bool(*ConditionFn)(ExecationContext&);

enum Control_Block_Type {
    BLOCK_WAIT,BLOCK_REPEAT,BLOCK_FOREVER,BLOCK_IF,BLOCK_IF_ELSE,
    BLOCK_WAIT_UNTIL,BLOCK_STOP_ALL,BLOCK_REPEAT_UNTIL,
    MARKER_ELSE,MARKER_END_IF,MARKER_BEGIN_REPEAT,MARKER_END_REPEAT,
    BLOCK_CALL_COMMAND,BLOCK_CALL_CONDITION_CONTROL_NONE
};

struct Control_Data {
    Control_Block_Type type;
    int valueI=0;
    double valueF=0.0;
    int jumpTO=-1;
    CommandFn commandFn=nullptr;
    ConditionFn conditionFn=nullptr;
};

struct DraggableControl {
    SDL_Texture* texture=nullptr;
    SDL_Rect rect = {0,0,0,0};
    int id=-1;
    int parentID=-1;
    Control_Block_Type type;

    bool dragging=false;
    int offsetX=0,offsetY=0;

    string inputValue="10";
    bool dropdownOpen=false;
    vector<string> options;
    int selectedOption=0;

    void updatePoistion(int nx,int ny) {
        rect.x=nx;
        rect.y=ny;
    }
};
static vector<DraggableControl> controlWorkspace;
static vector<DraggableControl> controlMenu;
static map<int,Control_Data> controlRuntime;
static int globalCtrlID=2000;

inline bool isPointInRect(int x,int y,SDL_Rect r) {
    return x>= r.x && x<= r.x+r.w && y>= r.y && y<= r.y+r.h;
}

inline bool PreprocessControlFlow(vector<Control_Data>& script) {
    int ifStack[500], ifTop=-1;
    int repStack[500], repTop=-1;

    for(int i=0;i<(int)script.size();i++) {
        if(script[i].type == BLOCK_IF) {
            ifStack[++ifTop]=i;
        }
        else if(script[i].type == MARKER_ELSE) {
            if (ifTop<0) return false;
            script[ifStack[ifTop]].jumpTO=i;
            ifStack[ifTop] = i;
        }
        else if(script[i].type == MARKER_END_IF) {
            if (ifTop<0) return false;
            script[ifStack[ifTop--]].jumpTO=i;
        }
        else if(script[i].type == BLOCK_REPEAT || script[i].type == BLOCK_FOREVER) {
            repStack[++repTop]=i;
        }
        else if (script[i].type == MARKER_END_REPEAT) {
            if (repTop<0) return false;
            int start=repStack[repTop--];
            script[start].jumpTO=i;
            script[i].jumpTO=start;
        }
    }
    return (ifTop==-1 && repTop==-1);
}

inline void HandleControlEvents(SDL_Event &e,int mx,int my) {
    if (e.type==SDL_MOUSEBUTTONDOWN) {
        for (int i=controlWorkspace.size()-1;i>=0;i--) {
            if (isPointInRect(mx,my,controlWorkspace[i].rect)) {
                controlWorkspace[i].dragging=true;
                controlWorkspace[i].offsetX=mx-controlWorkspace[i].rect.x;
                controlWorkspace[i].offsetY=my-controlWorkspace[i].rect.y;

                DraggableControl temp=controlWorkspace[i];
                controlWorkspace.erase(controlWorkspace.begin()+i);
                controlWorkspace.push_back(temp);
                return;
            }
        }
    }
    if (e.type==SDL_MOUSEBUTTONUP) {
        for (auto& b:controlWorkspace) {
            if (b.dragging) {
                b.dragging=false;

                for (auto& target:controlWorkspace) {
                    if (b.id==target.id) continue;
                    if ((abs(b.rect.x-target.rect.x)<30) && abs(b.rect.y-(target.rect.y+target.rect.h-6)<30)) {
                        b.rect.x=target.rect.x;
                        b.rect.y=target.rect.y+target.rect.h-6;
                        b.parentID=target.id;
                        break;
                    }
                }
            }
        }
    }
    if (e.type==SDL_MOUSEMOTION) {
        for (int i=0;i<controlWorkspace.size();i++) {
            if (controlWorkspace[i].dragging) {
                int dx=(mx-controlWorkspace[i].offsetX) - controlWorkspace[i].rect.x;
                int dy=(my-controlWorkspace[i].offsetY) - controlWorkspace[i].rect.y;

                vector<int> moveList;
                moveList.push_back(controlWorkspace[i].id);

                controlWorkspace[i].rect.x+=dx;
                controlWorkspace[i].rect.y+=dy;

                bool foundNew=true;
                while (foundNew) {
                    foundNew=false;
                    for (auto& child: controlWorkspace) {
                        if (find(moveList.begin(),moveList.end(),child.parentID)!=moveList.end() &&
                            find(moveList.begin(),moveList.end(),child.id)==moveList.end()){
                            child.rect.x+=dx;
                        child.rect.y+=dy;
                        moveList.push_back(child.id);
                        foundNew=true;
                        }
                    }
                }
            }
        }
    }
}
inline void RenderControlSystem(SDL_Renderer* ren) {
    for (auto& b:controlWorkspace) {
        SDL_RenderCopy(ren,b.texture,NULL,&b.rect);
        if (b.dropdownOpen) {

        }
    }
}



#endif //SCRATCH_PROJECT_CONTROLORDERS_H

#ifndef SCRATCH_PROJECT_OPERATOR_H
#define SCRATCH_PROJECT_OPERATOR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;
#define M_PI 3.1415
enum Operator_Block_Type {
    BLOCK_ADD,BLOCK_SUBTRACT,BLOCK_MULTIPLY,BLOCK_DIVIDE,BLOCK_RANDOM,
    BLOCK_GREATER_THAN,BLOCK_LESS_THAN,BLOCK_EQUAL,BLOCK_AND,BLOCK_OR,
    BLOCK_NOT,BLOCK_JOIN,BLOCK_LETTER_OF,BLOCK_LENGTH,BLOCK_CONTAINS,
    BLOCK_MOD,BLOCK_ROUND,BLOCK_ABS,BLOCK_NONE,
};
static vector<string> mathFunctions = {
    "abs","floor","ceiling","sqrt","sin","cos","tan","asin","acos","atan","ln","log","e ^","10 ^"
};

struct Operator_Block {
    Operator_Block_Type type;
    double numA=0.0;
    double numB=0.0;
    string strA="";
    string strB="";
    int mathFuncIndex=0;
    string result = "";
    bool showResult=false;
};
struct DraggableBlock {
    SDL_Texture *texture= nullptr;
    SDL_Rect rect={0,0,0,0};
    SDL_Rect boxA={0,0,45,22};
    SDL_Rect boxB={0,0,45,22};
    bool dragging = false;
    int offsetX=0,offsetY=0;
    int id=-1;
    Operator_Block_Type opType=BLOCK_NONE;
    string textA= "";
    string textB= "";
    bool hasSecondNumber=true;

    void updateBoxes(TTF_Font* font) {
        int twA=0,twB=0,th=0;

        if (!textA.empty() && font) TTF_SizeText(font,textA.c_str(),&twA,&th);
        boxA.w=max(40,twA+12);
        boxA.h=22;
        boxA.x=rect.x-boxA.w+12;
        boxA.y=rect.y+(rect.h/2) - (boxA.h/2);

        if (hasSecondNumber) {
            if (!textB.empty() && font) TTF_SizeText(font,textB.c_str(),&twB,&th);
            boxB.w=max(40,twB+12);
            boxB.h=22;
            boxB.x=rect.x+(rect.w) +5;
            boxB.y=rect.y+(rect.h/2) - (boxB.h/2);
        }
    }
};
static map<int,Operator_Block> operatorRuntimeData;
static vector<DraggableBlock> workspaceBlocks;
static vector<DraggableBlock> OperatorMenuBlocks;
static int globalBlockID=1000;
static int focusedBlockID=-1;
static int focusedField=0;
static TTF_Font* globalFont=nullptr;

inline bool isInside(int x,int y,SDL_Rect r) {
    return x>=r.x && x<=r.x+r.w && y>=r.y && y<=r.y+r.h;
}
inline string formatDoubleClean(double v) {
    if (isnan(v)) return "NaN";
    if (isinf(v)) return "Infinity";

    stringstream ss;
    ss << fixed << setprecision(4) << v;
    string s=ss.str();
    s.erase(s.find_last_not_of('0')+1,string::npos);
    if (s.back() == '.') s.pop_back();
    return s;
}

inline void EvaluateOperator(int id) {
    if (operatorRuntimeData.find(id)==operatorRuntimeData.end()) return;
        Operator_Block &blc=operatorRuntimeData[id];

        try {
            blc.numA=blc.strA.empty() ? 0.0 : stod(blc.strA);
            blc.numB = blc.strB.empty() ? 0.0 : stod(blc.strB);
        } catch (...) {
            blc.numA=0.0;
            blc.numB=0.0;
        }

        switch (blc.type) {
            case BLOCK_ADD:
                blc.result=formatDoubleClean(blc.numA + blc.numB);
                break;
            case BLOCK_SUBTRACT:
                blc.result=formatDoubleClean(blc.numA - blc.numB);
                break;
            case BLOCK_MULTIPLY:
                blc.result=formatDoubleClean(blc.numA * blc.numB);
                break;
            case BLOCK_DIVIDE:
                blc.result = (blc.numB!=0) ? formatDoubleClean(blc.numA / blc.numB) : "Infinity";
                break;
            case BLOCK_RANDOM: {
                int minV=(int)min(blc.numA,blc.numB);
                int maxV=(int)max(blc.numA,blc.numB);
                blc.result=to_string(minV + (rand()%(maxV-minV+1)));
                break;
            }
            case BLOCK_GREATER_THAN:
                blc.result=(blc.numA > blc.numB) ? "true" : "false";
                break;
            case BLOCK_LESS_THAN:
                blc.result=(blc.numA < blc.numB) ? "true" : "false";
                break;
            case BLOCK_EQUAL:
                blc.result=(blc.strA == blc.strB) ? "true" : "false";
                break;
            case BLOCK_AND:
                blc.result=(blc.numA !=0 && blc.numB!=0) ? "true" : "false";
                break;
            case BLOCK_OR:
                blc.result=(blc.numA != 0 || blc.numB != 0) ? "true" : "false";
                break;
            case BLOCK_NOT:
                blc.result=(blc.numA == 0 && blc.strA != "true") ? "true" : "false";
                break;
            case BLOCK_JOIN:
                blc.result = blc.strA + blc.strB;
                break;
            case BLOCK_LETTER_OF : {
                int idx=(int)blc.numA -1;
                if (idx>=0 && idx < (int)blc.strB.length())
                    blc.result=blc.strB[idx];
                else blc.result = "";
                break;
            }
            case BLOCK_LENGTH :
                blc.result = to_string(blc.strA.length());
                break;
            case BLOCK_CONTAINS :
                blc.result = (blc.strA.find(blc.strB) != string::npos) ? "true " : "false";
                break;
            case BLOCK_MOD:
                blc.result= formatDoubleClean(fmod(blc.numA,blc.numB));
                break;
            case BLOCK_ROUND:
                blc.result = formatDoubleClean(round(blc.numA));
                break;
            case BLOCK_ABS: {
                string func = mathFunctions[blc.mathFuncIndex];
                double v=blc.numA;
                double r = 0;
                if (func == "abs") r=abs(v);
                else if (func == "floor") r = floor(v);
                else if (func == "ceiling") r = ceil(v);
                else if (func == "sqrt") r = (v>=0) ? sqrt(v) : 0;
                else if (func == "sin") r=sin(v*M_PI/180.0);
                else if (func == "cos") r=cos(v*M_PI/180.0);
                else if (func == "tan") r=tan(v*M_PI/180.0);
                else if (func == "asin") r=asin(v)*180.0/M_PI;
                else if (func == "acos") r=acos(v)*180.0/M_PI;
                else if (func == "atan") r=atan(v)*180.0/M_PI;
                else if (func == "ln") r= (v>0) ? log(v) : 0;
                else if (func == "log") r= (v>0) ? log10(v) : 0;
                else if (func == "e ^") r=exp(v);
                else if (func == "10 ^") r=pow(10,v);
                blc.result = formatDoubleClean(r);
                break;
        }
        default:
            blc.result = "";
            break;
    }
    blc.showResult = true;
}




#endif //SCRATCH_PROJECT_OPERATOR_H

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