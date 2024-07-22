/**
  ******************************************************************************
  * @file           : closure.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/20
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_CLOSURE_HPP
#define LUA5_3_DECOMPILER_CLOSURE_HPP

#include "../binChunk/chunk_types.hpp"

class LuaState;

typedef int (*CPlusFunction)(LuaState&);

struct Closure {
    Prototype prototype;        // lua closure
    CPlusFunction cPlusFunc;    // c++ closure
    bool isLuaClosure;

    static Closure NewLuaClosure(Prototype proto) {
        return Closure{
            .prototype = proto,
            .cPlusFunc = nullptr,
            .isLuaClosure = true
        };
    }

    static Closure NewCPlusClosure(CPlusFunction func) {
        return Closure{
                .cPlusFunc = func,
                .isLuaClosure = false
        };
    }
};

#endif //LUA5_3_DECOMPILER_CLOSURE_HPP
