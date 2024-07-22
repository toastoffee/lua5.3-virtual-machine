/**
  ******************************************************************************
  * @file           : lua_stack.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_STACK_HPP
#define LUA5_3_DECOMPILER_LUA_STACK_HPP

#include "lua_value.hpp"
#include "closure.hpp"

#include <algorithm>

struct LuaStack {
public:
    LuaValue *_slots;
    int _slotSize;
    int _top;

public:
    LuaStack* _prev;
    Closure* _closure;
    std::vector<LuaValue> _varargs;
    int _pc;

public:

    LuaStack(LuaValue slots[], int slotSize, int top) :
        _slots(slots), _slotSize(slotSize), _top(top) { }

    static LuaStack* NewLuaStack(int size) {
        return new LuaStack(new LuaValue[size], size, 0);
    }

    void Check(int n) {
        int free = _slotSize - _top;
        if(n <= free) return;

        LuaValue* newSlots = new LuaValue[_top + n];
        _slotSize = _top + n;
        memcpy(newSlots, _slots, _top * sizeof(LuaValue));
        delete[] _slots;
        _slots = newSlots;
    }

    void Push(LuaValue val) {
        assert(_top < _slotSize && "stack overflow!");

        _slots[_top] = val;
        _top++;
    }

    LuaValue Pop() {
        assert(_top >= 1 && "stack underflow!");

        _top--;
        LuaValue val = _slots[_top];
        _slots[_top] = LuaValue();
        return val;
    }

    int AbsIndex(int idx) {
        if (idx >= 0) {
            return idx;
        }
        return idx + _top + 1;
    }

    bool IsValid(int idx) {
        int absIdx = AbsIndex(idx);
        return absIdx > 0 && absIdx <= _top;
    }

    LuaValue Get(int idx) {
        int absIdx = AbsIndex(idx);

        if(IsValid(absIdx)) {
            return _slots[absIdx-1];
        }
        return LuaValue();
    }

    void Set(int idx, LuaValue val) {
        int absIdx = AbsIndex(idx);
        assert(absIdx > 0 && absIdx <= _top && "invalid index!");

        _slots[absIdx-1] = val;
        return;
    }

    int GetTop() const {
        return _top;
    }

    void Reverse(int from, int to) {
        if(to > from) {
            std::reverse(_slots + from, _slots + to + 1);
        } else if(to < from) {
            Reverse(to, from);
        }
    }

    std::vector<LuaValue> PopN(int n){
        std::vector<LuaValue> vals;
        for (int i = n - 1; i >= 0 ; i--) {
            vals.insert(vals.begin(), Pop());
        }
        return vals;
    }

    void PushN(std::vector<LuaValue> vals, int n){
        int nVals = vals.size();
        if(n < 0){ n = nVals; }
        for (int i = 0; i < n; i++) {
            if(i < nVals) {
                Push(vals[i]);
            } else {
                Push(LuaValue());
            }
        }
    }

    void PushCPlusFunction(CPlusFunction f) {

    }

    bool IsCPlusFunction(int idx) {

    }

    CPlusFunction ToCPlusFunction(int idx) {

    }
};

#endif //LUA5_3_DECOMPILER_LUA_STACK_HPP
