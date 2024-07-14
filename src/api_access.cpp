/**
  ******************************************************************************
  * @file           : api_access.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */

#include "lua_state.hpp"

std::string LuaState::TypeName(LuaType tp) {
    switch (tp) {
        case LUA_TNONE:     return "no value";
        case LUA_TNIL:      return "nil";
        case LUA_TBOOLEAN:  return "boolean";
        case LUA_TNUMBER:   return "number";
        case LUA_TSTRING:   return "string";
        case LUA_TTABLE:    return "table";
        case LUA_TFUNCTION: return "function";
        case LUA_TTHREAD:   return "thread";
        default:            return "userdata";
    }
}

LuaType LuaState::Type(int idx) {
    if(_stack->IsValid(idx)) {
        LuaValue val = _stack->Get(idx);
        return TypeOf(val);
    }
    return LUA_TNONE;
}

bool LuaState::IsNone(int idx) {
    return Type(idx) == LUA_TNONE;
}

bool LuaState::IsNil(int idx) {
    return Type(idx) == LUA_TNIL;
}

bool LuaState::IsNoneOrNil(int idx) {
    return IsNone(idx) || IsNil(idx);
}

bool LuaState::IsBoolean(int idx) {
    return Type(idx) == LUA_TBOOLEAN;
}

bool LuaState::IsString(int idx) {
    return Type(idx) == LUA_TSTRING || Type(idx) == LUA_TNUMBER;
}

bool LuaState::IsNumber(int idx) {
    auto t = ToNumberX(idx);
    return std::get<1>(t);
}

bool LuaState::IsInteger(int idx) {
    LuaValue val = _stack->Get(idx);
    return val.GetType() == typeid(int64).name();
}


