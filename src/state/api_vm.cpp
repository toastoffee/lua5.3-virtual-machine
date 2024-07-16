/**
  ******************************************************************************
  * @file           : api_vm.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */

#include "../api/lua_state.hpp"

int LuaState::PC() {
    return _pc;
}

void LuaState::AddPC(int n) {
    _pc += n;
}

Instruction LuaState::Fetch() {
    Instruction i = _proto->code[_pc];
    _pc++;
    return i;
}

void LuaState::GetConst(int idx) {
    Constant c = _proto->constants[idx];
    _stack->Push(LuaValue::ConvertFromConst(c));
}

void LuaState::GetRK(int rk) {
    if(rk > 0xff) {
        GetConst(rk & 0xff);
    } else{
        PushValue(rk + 1);
    }
}