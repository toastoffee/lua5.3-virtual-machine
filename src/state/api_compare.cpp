/**
  ******************************************************************************
  * @file           : api_compare.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */

#include "../api/lua_state.hpp"

bool _eq(LuaValue a, LuaValue b) {
    if(a.GetType() == typeid(Nil).name()) {
        return b.GetType() == typeid(Nil).name();
    }
    else if (a.GetType() == typeid(bool).name()) {
        return (b.GetType() == typeid(bool).name())
        && (a.ConvertToBoolean(a) == b.ConvertToBoolean(b));
    }
    else if (a.GetType() == typeid(std::string).name()) {
        return (b.GetType() == typeid(std::string).name())
        && (a.GetVal<std::string>() == b.GetVal<std::string>());
    }
    else if (a.GetType() == typeid(int64).name()) {
        if(b.GetType() == typeid(int64).name()) {
            return a.GetVal<int64>() == b.GetVal<int64>();
        }
        else if (b.GetType() == typeid(float64).name()) {
            return (float64) a.GetVal<int64>() == b.GetVal<float64>();
        }
        else {
            return false;
        }
    }
    else if (a.GetType() == typeid(float64).name()) {
        if(b.GetType() == typeid(float64).name()) {
            return a.GetVal<float64>() == b.GetVal<float64>();
        }
        else if (b.GetType() == typeid(int64).name()) {
            return a.GetVal<float64>() == (float64) b.GetVal<int64>();
        }
        else {
            return false;
        }
    }
    else {
        return a.GetVal<int64>() == b.GetVal<int64>();
    }
}

bool _lt(LuaValue a, LuaValue b) {
    if(a.GetType() == typeid(std::string).name()) {
        return (b.GetType() == typeid(std::string).name())
               && (a.GetVal<std::string>() < b.GetVal<std::string>());
    }
    else if (a.GetType() == typeid(int64).name()) {
        if(b.GetType() == typeid(int64).name()) {
            return a.GetVal<int64>() < b.GetVal<int64>();
        }
        else if (b.GetType() == typeid(float64).name()) {
            return (float64) a.GetVal<int64>() < b.GetVal<float64>();
        }
    }
    else if (a.GetType() == typeid(float64).name()) {
        if(b.GetType() == typeid(float64).name()) {
            return a.GetVal<float64>() < b.GetVal<float64>();
        }
        else if (b.GetType() == typeid(int64).name()) {
            return a.GetVal<float64>() < (float64) b.GetVal<int64>();
        }
    }

    assert(false && "comparison error!");
}

bool _le(LuaValue a, LuaValue b) {
    if(a.GetType() == typeid(std::string).name()) {
        return (b.GetType() == typeid(std::string).name())
               && (a.GetVal<std::string>() <= b.GetVal<std::string>());
    }
    else if (a.GetType() == typeid(int64).name()) {
        if(b.GetType() == typeid(int64).name()) {
            return a.GetVal<int64>() <= b.GetVal<int64>();
        }
        else if (b.GetType() == typeid(float64).name()) {
            return (float64) a.GetVal<int64>() <= b.GetVal<float64>();
        }
    }
    else if (a.GetType() == typeid(float64).name()) {
        if(b.GetType() == typeid(float64).name()) {
            return a.GetVal<float64>() <= b.GetVal<float64>();
        }
        else if (b.GetType() == typeid(int64).name()) {
            return a.GetVal<float64>() <= (float64) b.GetVal<int64>();
        }
    }

    assert(false && "comparison error!");
}



bool LuaState::Compare(int idx1, int idx2, CompareOp op) {
    LuaValue a = _stack->Get(idx1);
    LuaValue b = _stack->Get(idx2);

    switch (op) {
        case LUA_OPEQ:
            return _eq(a, b);
        case LUA_OPLT:
            return _lt(a, b);
        case LUA_OPLE:
            return _le(a, b);
        default:
            assert(false && "invalid compare op!");
    }
}