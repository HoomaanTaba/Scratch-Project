
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