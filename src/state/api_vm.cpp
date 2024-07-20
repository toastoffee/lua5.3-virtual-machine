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
    return _stack->_pc;
}

void LuaState::AddPC(int n) {
    _stack->_pc += n;
}

Instruction LuaState::Fetch() {
    Instruction i = _stack->_closure->prototype->code[_stack->_pc];
    _stack->_pc++;
    return i;
}

void LuaState::GetConst(int idx) {
    Constant c = _stack->_closure->prototype->constants[idx];
    _stack->Push(LuaValue::ConvertFromConst(c));
}

void LuaState::GetRK(int rk) {
    if(rk > 0xff) {
        GetConst(rk & 0xff);
    } else{
        PushValue(rk + 1);
    }
}