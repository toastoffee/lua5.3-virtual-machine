/**
  ******************************************************************************
  * @file           : inst_operators.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */

#include "inst.h"

void _binaryArith(Instruction i, LuaVM vm, ArithOp op) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    vm.GetRK(b);
    vm.GetRK(c);
    vm.Arith(op);
    vm.Replace(a);
}

void _unaryArith(Instruction i, LuaVM vm, ArithOp op) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;

    vm.PushValue(b);
    vm.Arith(op);
    vm.Replace(a);
}

void add(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPADD); }
void sub(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSUB); }
void mul(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPMUL); }
void mod(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPMOD); }
void pow(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPPOW); }
void div(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPDIV); }
void idiv(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPIDIV); }
void band(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBAND); }
void bor(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBOR); }
void bxor(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBXOR); }
void shl(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSHL); }
void shr(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSHR); }
void unm(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPUNM); }
void bnot(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBNOT); }