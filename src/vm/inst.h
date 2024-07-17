/**
  ******************************************************************************
  * @file           : inst.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_INST_H
#define LUA5_3_DECOMPILER_INST_H

#include "../state/lua_value.hpp"
#include "../api/lua_state.hpp"

#include "instruction_types.hpp"
#include "instruction_decode.hpp"

typedef LuaState LuaVM;

class Inst {

    static void Move(Instruction i, LuaVM vm);
    static void Jmp(Instruction i, LuaVM vm);

    static void LoadNil(Instruction i, LuaVM vm);
    static void LoadBool(Instruction i, LuaVM vm);
    static void LoadK(Instruction i, LuaVM vm);
    static void LoadKx(Instruction i, LuaVM vm);

    static void Add(Instruction i, LuaVM vm);
    static void Sub(Instruction i, LuaVM vm);
    static void Mul(Instruction i, LuaVM vm);
    static void Mod(Instruction i, LuaVM vm);
    static void Pow(Instruction i, LuaVM vm);
    static void Div(Instruction i, LuaVM vm);
    static void Idiv(Instruction i, LuaVM vm);
    static void Band(Instruction i, LuaVM vm);
    static void Bor(Instruction i, LuaVM vm);
    static void Bxor(Instruction i, LuaVM vm);
    static void Shl(Instruction i, LuaVM vm);
    static void Shr(Instruction i, LuaVM vm);
    static void Unm(Instruction i, LuaVM vm);
    static void Bnot(Instruction i, LuaVM vm);
};

#endif //LUA5_3_DECOMPILER_INST_H
