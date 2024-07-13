/**
  ******************************************************************************
  * @file           : instruction_decode.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/13
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_INSTRUCTION_DECODE_HPP
#define LUA5_3_DECOMPILER_INSTRUCTION_DECODE_HPP

#include "instruction_types.hpp"
#include "chunk_types.hpp"

const int MAX_ARG_Bx = (1 << 18) - 1;
const int MAX_ARG_sBx = MAX_ARG_Bx >> 1;

uint32 GetOpcode(Instruction i) {
    return i & 0x3f;
}

void ABC(Instruction i, int& a, int& b, int& c) {
    a = (int)((i >> 6) & 0xff);
    b = (int)((i >> 14) & 0x1ff);
    c = (int)((i >> 23) & 0x1ff);
    return;
}

void ABx(Instruction i, int& a, int& bx) {
    a =  (int)((i >> 6) & 0xff);
    bx = (int)(i >> 14);
    return;
}

void AsBx(Instruction i, int& a, int& sbx) {
    ABx(i, a, sbx);
    sbx -= MAX_ARG_sBx;
    return;
}

void Ax(Instruction i, int& a) {
    a = (int)(i >> 6);
    return;
}

#endif //LUA5_3_DECOMPILER_INSTRUCTION_DECODE_HPP
