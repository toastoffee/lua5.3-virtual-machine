/**
  ******************************************************************************
  * @file           : inst_misc.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */

#include "inst.h"

void Inst::Move(Instruction i, LuaVM vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;
    vm.Copy(b, a);
}

void Inst::Jmp(Instruction i, LuaVM vm) {
    int a, sbx;
    AsBx(i, a, sbx);
    vm.AddPC(sbx);

    assert(a == 0 && "todo!");
}