

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