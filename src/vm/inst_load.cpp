/**
  ******************************************************************************
  * @file           : inst_load.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */


#include "inst.h"

void Inst::LoadNil(Instruction i, LuaVM vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;

    vm.PushNil();
    for (int j = a; j < a+b; ++j) {
        vm.Copy(-1, j);
    }
    vm.Pop(1);
}

void Inst::LoadBool(Instruction i, LuaVM vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    vm.PushBoolean(b != 0);
    vm.Replace(a);
    if(c != 0) {
        vm.AddPC(1);
    }
}

void Inst::LoadK(Instruction i, LuaVM vm) {
    int a, bx;
    ABx(i, a, bx);
    a += 1;

    vm.GetConst(bx);
    vm.Replace(a);
}

void Inst::LoadKx(Instruction i, LuaVM vm) {
    int a, _;
    ABx(i, a, _);
    a += 1;

    int ax;
    Ax(vm.Fetch(),ax);

    vm.GetConst(ax);
    vm.Replace(a);
}