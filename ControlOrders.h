
#ifndef SCRATCH_CONTROLORDERS_H
#define SCRATCH_CONTROLORDERS_H

#endif //SCRATCH_CONTROLORDERS_H

//the logic of control orders as in 4.5 in project doc
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;
struct ExucationContext {
    bool isRunning=true; //if true stops this scrip
    bool stopAll=false; //if true stops the project
    int watchdogCounter=0; //for the unlimited loops
    SDL_Renderer* renderer=nullptr;
};
typedef void(*CommandFn)(ExucationContext&);
typedef bool (*ConditionFn)(ExucationContext&);
//defining of all the blocks that we need to make and beacuse the control orders mostly work with other orders (moving orders etc) we need to define command and conditions too for some of the orders
enum Control_Block_Type {
    //control blocks
    BLOCK_WAIT,
    BLOCK_REPEAT,
    BLOCK_FOREVER,
    BLOCK_IF,
    BLOCK_IF_ELSE,
    BLOCK_WAIT_UNTIL,
    BLOCK_STOP_ALL,
    BLOCK_REPEAT_UNTIL,

    //not visible in the UI
    MARKER_ELSE,
    MARKER_END_IF,
    MARKER_BEGIN_REPEAT,
    MARKER_END_REPEAT,

    //for non control blocks ( moves looks etc)
    BLOCK_CALL_COMMAND,
    BLOCK_CALL_CONDITION,
};

//the struct which we need to use for each order
struct Operator_Block {
        Control_Block_Type type; //wait if repeat etc
    int valueI=0; // int parameter for amount of repeat
    double valueF=0.0;  //double parameter for the amount of waiting
    CommandFn commandFn=nullptr; //for excucatable commands (eg;move 10 steps)
    ConditionFn conditionFn=nullptr; //for conditions (eg : if,wait_until)
    int jumpTo=-1;
};
//wathchdog for checking the infinite loops and avoiding errors and hang
bool CheckWatchdog(
    ExucationContext& ctx,
    int limit=10000) {
    ctx.wathdogCounter++;

    if (ctx.watchdogCounter>limit) {
        ctx.isRunning=false;
        return true;
    }
    return false;
}

//control blocks (4.5.2 in the project doc)
void WAIT_BLOCK(Operator_Block& blc,ExucationContext&ctx) {
    SDL_Delay((Uint32)(blc.valueF*1000));
}

void WAIT_UNTIL_BLOCK(Operator_Block& blc,ExucationContext&ctx) {
    if (!blc.conditionFn) return; //if the condition does not apply dont do anything
    while (!blc.conditionFn(ctx)&&ctx.isRunning && !ctx.stopAll) {
        SDL_Delay(10); //else wait (with the three coniditons true: apllying conditions + running scrips + not stopped)
    }
}

void IF_BLOCK(Operator_Block& blc,ExucationContext&ctx,int& ip,vector<Operator_Block>& prog) {
    if (!blc.conditionFn(ctx)) {
        ip=blc.jumpTo; //if the condition does not apply it jumps from the if
    }
}

void ELSE_BLOCK(Operator_Block& blc,int& ip) {
    ip=blc.jumpTo;
}

void END_REPEAT_BLOCK(Operator_Block& blc,ExucationContext&ctx, int &ip,vector<Operator_Block>&prog) {
    int beginIndex=blc.jumpTo;
    if (prog[beginIndex].type==BLOCK_REPEAT) {
        Block& rep=prog[beginIndex];
        rep.valueI--;
        if (rep.valueI>0) {
            ip.beginIndex-1;
        }
        //continue the loop until valueI is over
    }
}

void FOREVER_BLOCK(Operator_Block& blc,ExucationContext& ctx) {
while (ctx.isRunning && !ctx.stopAll) {
    SDL_Delay(1); //infinite loop
}
}

void STOP_ALL_BLOCK(ExucationContext& ctx) {
    ctx.stopAll=true; //stopping the entire scratch project
}
void REPEAT_UNTIL_BLOCK(Operator_Block& blc,ExucationContext& ctx,int& ip,vector<Operator_Block>&prog){
    if (!blc.conditionFn(ctx)) {
        ip=blc.jumpTo; //a conditional loop
    }
}

void CALL_COMMAND(Operator_Block& blc,ExucationContext& ctx) {
    if (blc.commandFn) ins.commandFn(ctx);
}

void CALL_CONDITION(Operator_Block& blc,ExucationContext& ctx,int& ip,vector<Operator_Block>&prog) {
    if (!blc.conditionFn(ctx)) {
        ip=blc.jumpTo;
    }
}
//preprocessing (4.5.1 in the project doc)
bool PreprocessScript(
    vector<Operator_Block>&prog) {

    int ifStack[1000];
    int ifTop=-1;

    int repeatStack[1000];
    int repeatTop=-1;

    for (int i=0;i<(int)prog.size();i++) {
        Operator_Block &blck=prog[i];
        //IF Algorithm (matching the IF and ELSE and END together)
        if (blck.type==BLOCK_IF) {
            ifTop++;
            ifStack[ifTop]=i;
        }
        else if (blck.type==MARKER_ELSE) {
            if (ifTop<0) return false;
            int ifIndex=ifStack[ifTop];
            prog[ifIndex].jumpTo=i;
            ifStack[ifTop]=i;
        }
        else if (blck.type==MARKER_END_IF) {
            if (ifTop<0) return false;
            int openIndex=ifStack[ifTop];
            ifTop--;

            prog[openIndex].jumpTo=i;
        }

        //REPEAT Algorithm (matching the begining and end)
        else if (blck.type==MARKER_BEGIN_REPEAT) {
            repeatTop++;
            repeatStack[repeatTop]=i;

        }
        else if (blck.type==MARKER_END_REPEAT) {
            if (repeatTop<0) return false;
            int beginIndex=repeatStack[repeatTop];
            repeatTop--;

            prog[beginIndex].jumpTo=i;
            prog[i].jumpTo=beginIndex;
        }
    }
    if (ifTop!=-1) return false;
    if (repeatTop!=-1) return false;
    return true;
}
