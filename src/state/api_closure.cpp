/**
  ******************************************************************************
  * @file           : api_closure.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/21
  ******************************************************************************
  */

#include "../api/lua_state.hpp"


int LuaState::RegisterCount() {
    return (int)_stack->_closure->prototype.maxStackSize;
}

void LuaState::LoadVararg(int n) {
    if(n < 0) {
        n = _stack->_varargs.size();
    }
    _stack->Check(n);
    _stack->PushN(_stack->_varargs, n);
}

void LuaState::LoadProto(int idx) {
    auto proto = _stack->_closure->prototype.prototypes[idx];
    auto closure = Closure{.prototype = proto};
    _stack->Push(LuaValue(closure));
}