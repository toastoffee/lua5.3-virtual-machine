/**
  ******************************************************************************
  * @file           : lua_state.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_STATE_HPP
#define LUA5_3_DECOMPILER_LUA_STATE_HPP

#include "lua_stack.hpp"

typedef int LuaType;

class LuaState {
private:
    LuaStack _stack;
    Prototype proto;
    int pc;

public:
    /* basic stack manipulation */
    int GetTop();
    int AbsIndex();
    bool CheckStack(int n);
    void Pop(int n);
    void Copy(int fromIdx, int toIdx);
    void PushValue(int idx);
    void Replace(int idx);
    void Insert(int idx);
    void Remove(int idx);
    void Rotate(int idx, int n);
    void SetTop(int idx);

    /* access functions (stack -> c++) */
    std::string TypeName(LuaType tp);
    LuaType Type(int idx);
    bool IsNone(int idx);
    bool IsNil(int idx);
    bool IsNoneOrNil(int idx);
    bool IsBoolean(int idx);
    bool IsInteger(int idx);
    bool IsNumber(int idx);
    bool IsString(int idx);
    bool ToBoolean(int idx);
    bool ToInteger(int idx);
    bool ToIntegerX(int idx);
    bool ToNumber(int idx);
    bool ToNumberX(int idx);
    bool ToString(int idx);
    bool ToStringX(int idx);

    /* push functions (c++ -> stack) */
    void PushNil();
    void PushBoolean(bool b);
    void PushInteger(int64 n);
    void PushNumber(float64 n);
    void PushString(std::string s);
};

#endif //LUA5_3_DECOMPILER_LUA_STATE_HPP
