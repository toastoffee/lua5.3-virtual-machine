/**
  ******************************************************************************
  * @file           : api_arith.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */

#include "../api/lua_state.hpp"
#include "../number/math.h"

/* basic funcs */
int64 iadd(int64 a, int64 b) { return  a + b;}
float64 fadd(float64 a, float64 b) { return  a + b;}

int64 isub(int64 a, int64 b) { return  a - b;}
float64 fsub(float64 a, float64 b) { return  a - b;}

int64 imul(int64 a, int64 b) { return  a * b;}
float64 fmul(float64 a, float64 b) { return  a * b;}

int64 imod(int64 a, int64 b) { return IMod(a, b);}
float64 fmod(float64 a, float64 b) { return FMod(a, b);}

float64 pow(float64 a, float64 n) {return std::pow(a, n);}
float64 div(float64 a, float64 b) { return a / b;}

int64 iidiv(int64 a, int64 b) { return IFloorDiv(a, b);}
float64 fidiv(float64 a, float64 b) {return FFloorDiv(a, b);}

int64 band(int64 a, int64 b) { return  a & b;}
int64 bor(int64 a, int64 b) { return  a | b;}
int64 bxor(int64 a, int64 b) { return  a ^ b;}

int64 shl(int64 a, int64 n) { return ShiftLeft(a, n); }
int64 shr(int64 a, int64 n) { return ShiftRight(a, n); }

int64 iunm(int64 a, int64 _) { return -a; }
float64 funm(float64 a, float64 _) { return -a; }
int64 bnot(int64 a, int64 _) { return ~a; }



struct Operator {
    int64 (*integerFunc)(int64, int64);
    float64 (*floatFunc)(float64, float64);
};

Operator operators[] = {
        Operator{iadd,    fadd },
        Operator{isub,    fsub },
        Operator{imul,    fmul },
        Operator{imod,    fmul },
        Operator{nullptr, pow  },
        Operator{nullptr, div  },
        Operator{iidiv,   fidiv},
        Operator{band,    nullptr  },
        Operator{bor,     nullptr  },
        Operator{bxor,    nullptr  },
        Operator{shl,    nullptr  },
        Operator{shr,    nullptr  },
        Operator{iunm,   funm },
        Operator{bnot,   nullptr  },
};


LuaValue _arith(LuaValue a, LuaValue b, Operator op) {
    if(op.floatFunc == nullptr) {   // bitwise
        auto x = a.ConvertToInteger(a);
        if(std::get<1>(x)) {
            auto y = a.ConvertToInteger(b);
            if(std::get<1>(y)) {
                int64 r = op.integerFunc(std::get<0>(x), std::get<0>(y));
                return LuaValue(r);
            }
        }
    } else {    // arith
        if(op.integerFunc != nullptr) {     // add,sub,mul,mod,idiv,unm
            auto x = a.ConvertToInteger(a);
            if(std::get<1>(x)) {
                auto y = a.ConvertToInteger(b);
                if(std::get<1>(y)) {
                    int64 r = op.integerFunc(std::get<0>(x), std::get<0>(y));
                    return LuaValue(r);
                }
            }
        }
        auto x = a.ConvertToFloat(a);
        if(std::get<1>(x)) {
            auto y = a.ConvertToFloat(b);
            if(std::get<1>(y)) {
                float64 r = op.floatFunc(std::get<0>(x), std::get<0>(y));
                return LuaValue(r);
            }
        }
    }

    return LuaValue();
}

void LuaState::Arith(ArithOp op) {
    LuaValue a, b;
    b = _stack->Pop();
    if(op != LUA_OPUNM && op != LUA_OPBNOT) {
        a = _stack->Pop();
    } else {
        a = b;
    }

    Operator opFuncs = operators[op];

    LuaValue res = _arith(a, b, opFuncs);
    if(res.GetType() != typeid(Nil).name()) {
        _stack->Push(res);
    } else {
        assert(false && "arithmetic error!");
    }
}
