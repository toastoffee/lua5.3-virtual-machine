/**
  ******************************************************************************
  * @file           : api_push.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */

#include "../api/lua_state.hpp"

void LuaState::PushNil() {
    _stack->Push(nil);
}

void LuaState::PushBoolean(bool b) {
    _stack->Push(LuaValue(b));
}

void LuaState::PushInteger(int64 n) {
    _stack->Push(LuaValue(n));
}

void LuaState::PushNumber(float64 n) {
    _stack->Push(LuaValue(n));
}

void LuaState::PushString(std::string s) {
    _stack->Push(LuaValue(s));
}