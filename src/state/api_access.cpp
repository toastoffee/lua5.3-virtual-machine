/**
  ******************************************************************************
  * @file           : api_access.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */

#include "../api/lua_state.hpp"

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
        return val.TypeOf(val);
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

bool LuaState::ToBoolean(int idx) {
    LuaValue val = _stack->Get(idx);
    return val.ConvertToBoolean(val);
}

float64 LuaState::ToNumber(int idx) {
    auto t = ToNumberX(idx);
    return std::get<0>(t);
}

std::tuple<float64, bool> LuaState::ToNumberX(int idx) {
    LuaValue val = _stack->Get(idx);

    return val.ConvertToFloat(val);
}

int64 LuaState::ToInteger(int idx) {
    auto t = ToIntegerX(idx);
    return std::get<0>(t);
}

std::tuple<int64, bool> LuaState::ToIntegerX(int idx) {
    LuaValue val = _stack->Get(idx);

//    if(val.GetType() == typeid(int64).name()) {
//        return std::make_tuple(val.GetVal<int64>(), true);
//    } else{
//        return std::make_tuple(0, false);
//    }

    return val.ConvertToInteger(val);
}

std::string LuaState::ToString(int idx) {
    auto t = ToStringX(idx);
    return std::get<0>(t);
}

std::tuple<std::string, bool> LuaState::ToStringX(int idx) {
    LuaValue val = _stack->Get(idx);

    if(val.GetType() == typeid(std::string).name()) {
        return std::make_tuple(val.GetVal<std::string>(), true);
    }
    else if(val.GetType() == typeid(int64).name()) {
        std::string s = std::to_string(val.GetVal<int64>());
        _stack->Set(idx, LuaValue(s));
        return std::make_tuple(s, true);
    }
    else if(val.GetType() == typeid(float64).name()) {
        std::string s = std::to_string(val.GetVal<float64>());
        _stack->Set(idx, LuaValue(s));
        return std::make_tuple(s, true);
    }
    else {
        return std::make_tuple("", false);
    }
}