

#ifndef SCRATCH_OPERATORS_H
#define SCRATCH_OPERATORS_H

#endif //SCRATCH_OPERATORS_H
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;
//defining all of blocks
enum Operator_Block_Type {
    //math operators
    BLOCK_ADD,
    BLOCK_SUBTRACT,
    BLOCK_MULTIPLY,
    BLOCK_DIVIDE,

    BLOCK_RANDOM,

    //comparison operators
    BLOCK_GREATER_THAN,
    BLOCK_LESS_THAN,
    BLOCK_EQUAL,

    //logical operators
    BLOCK_AND,
    BLOCK_OR,
    BLOCK_NOT,

    //string operators
    BLOCK_JOIN,
    BLOCK_NTH_LETTER,
    BLOCK_LENGTH,
    BLOCK_CONTAINS,

    //score operators
    BLOCK_MOD,
    BLOCK_ROUND,
    BLOCK_ABS,
    BLOCK_FLOOR,
    BLOCK_CEILING,
    BLOCK_SQRT,
    BLOCK_SIN,
    BLOCK_COS,
    BLOCK_TAN,
    BLOCK_ASIN,
    BLOCK_ACOS,
    BLOCK_ATAN,
    BLOCK_LN,
    BLOCK_LOG,
    BLOCK_EXP,
    BLOCK_POWER_10,
};
//this struct was made based on the explanation of the 4.7.3 in the project doc
struct Operator_Block {
    Operator_Block_Type type;
    //number inputs
    double numA=0;
    double numB=0;
    //boolian inputs
    bool boolA=false;
    bool boolB=false;
    //string inputs
    string strA;
    string strB;
    //results
    double numRes;
    bool boolRes;
    string stringRes;
};
//mathamethical functions
void ADD_BLOCK(Operator_Block& blc) {
    blc.NumRes=blc.numA+blc.numB;
}
void SUBTRACT_BLOCK(Operator_Block& blc) {
    blc.NumRes=blc.numA-blc.numB;
}
void MULTIPLY_BLOCK(Operator_Block& blc) {
    blc.NumRes=blc.numA*blc.numB;
}
void DIVIDE_BLOCK(Operator_Block& blc) {
    if (blc.numB==0) blc.numRes=0;
    else blc.numRes=blc.numA/blc.numB;
}
//we need to make it so that if both given numbers are int the random number would be int too
bool IsInt(double x) {
    return floor(x)==x;
}
void RANDOM_BLOCK(Operator_Block& blc) {
    double A=blc.numA;
    double B=blc.numB;
    if (A>B) swap(A,B);
    if (IsInt(A) && IsInt(B)) {
        int min=(int)A;
        int max=(int)B;
        int r=min+rand()%(max-min+1);
        blc.numRes=r;
    }
    else {
        double r=(double)rand()/RAND_MAX;
        blc.numRes=A+r*(B-A);
    }
}
//comparison functions
void GREATER_THAN_BLOCK(Operator_Block& blc) {
    blc.boolRes=blc.numA>blc.numB;
}

void LESS_THAN_BLOCK(Operator_Block& blc) {
    blc.boolRes=blc.numA<blc.numB;
}

void EQUAL_BLOCK(Operator_Block& blc) {
    blc.boolRes=blc.numA==blc.numB;
}
//logical functions
void AND_BLOCK(Operator_Block& blc) {
    blc.boolRes=blc.boolA&&blc.boolB;
}

void OR_BLOCK(Operator_Block& blc) {
    blc.boolRes=blc.boolA||blc.boolB;
}

void NOT_BLOCK(Operator_Block& blc) {
    blc.boolRes=!blc.boolA;
}
//string functions
void JOIN_BLOCK(Operator_Block& blc) {
    blc.stringRes=blc.strA+blc.strB;
}

void NTH_LETTER_BLOCK(Operator_Block& blc) {
    blc.stringRes=blc.strA[blc.numA];
}

void LENGTH_BLOCK(Operator_Block& blc) {
    blc.numRes=blc.strA.length();
}

void CONTAINS_BLOCK(Operator_Block& blc) {
    if (blc.strA.find(blc.strB)!=string::npos) blc.boolRes=true;
    else blc.boolRes=false;
}

//score operators functions which are listed in the 4.7.2 in the project doc (Nearly all of these are just CMATH functions with little to no change)
void MOD_BLOCK(Operator_Block& blc) {
    blc.numRes=(blc.numA)%(blc.numB);
}

void ROUND_BLOCK(Operator_Block& blc) {
    blc.numRes=round(blc.numA);
}

void ABS_BLOCK(Operator_Block& blc) {
    blc.numRes=abs(blc.numA);
}

void FLOOR_BLOCK(Operator_Block& blc) {
    blc.numRes=floor(blc.numA);
}

void CEILING_BLOCK(Operator_Block& blc) {
    blc.numRes=ceil(blc.numA);
}

void SQRT_BLOCK(Operator_Block& blc) {
    blc.numRes=sqrt(blc.numA);
}

void SIN_BLOCK(Operator_Block& blc) {
    blc.numRes=sin(blc.numA);
}

void COS_BLOCK(Operator_Block& blc) {
    blc.numRes=cos(blc.numA);
}

void TAN_BLOCK(Operator_Block& blc) {
    blc.numRes=tan(blc.numA);
}

void ASIN_BLOCK(Operator_Block& blc) {
    blc.numRes=asin(blc.numA);
}

void ACOS_BLOCK(Operator_Block& blc) {
    blc.numRes=acos(blc.numA);
}

void ATAN_BLOCK(Operator_Block& blc) {
    blc.numRes=atan(blc.numA);
}

void LN_BLOCK(Operator_Block& blc) {
    blc.numRes=log(blc.numA);
}
void LOG_BLOCK(Operator_Block& blc) {
    blc.numRes=log10(blc.numA);
}
void EXP_BLOCK(Operator_Block& blc) {
    blc.numRes=exp(blc.numA);
}
void POWER_10_BLOCK(Operator_Block& blc) {
    blc.numRes=pow(10,blc.numA);
}

