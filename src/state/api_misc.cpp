/**
  ******************************************************************************
  * @file           : api_misc.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */

#include "lua_state.hpp"

void LuaState::Len(int idx) {
    LuaValue val = _stack->Get(idx);

    if(val.GetType() == typeid(std::string).name()) {
        auto newVal = LuaValue((int64)val.GetVal<std::string>().length());
        _stack->Push(newVal);
    } else {
        assert(false && "length error!");
    }
}

void LuaState::Concat(int n) {
    if (n == 0) {
        _stack->Push(LuaValue(""));
    }
    else if(n >= 2) {
        for (int i = 1; i < n; ++i) {
            if(IsString(-1) && IsString(-2)) {
                std::string s2 = ToString(-1);
                std::string s1 = ToString(-2);
                _stack->Pop();
                _stack->Pop();
                _stack->Push(LuaValue(s1 + s2));
                continue;
            }
            assert(false && "concatenation error!");
        }
    }
}