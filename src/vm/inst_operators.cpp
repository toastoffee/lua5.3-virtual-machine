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

void Inst::Add(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPADD); }
void Inst::Sub(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSUB); }
void Inst::Mul(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPMUL); }
void Inst::Mod(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPMOD); }
void Inst::Pow(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPPOW); }
void Inst::Div(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPDIV); }
void Inst::Idiv(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPIDIV); }
void Inst::Band(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBAND); }
void Inst::Bor(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBOR); }
void Inst::Bxor(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBXOR); }
void Inst::Shl(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSHL); }
void Inst::Shr(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPSHR); }
void Inst::Unm(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPUNM); }
void Inst::Bnot(Instruction i, LuaVM vm) { _binaryArith(i, vm, LUA_OPBNOT); }