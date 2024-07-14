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


struct LuaStack {
private:
    LuaValue *_slots;
    int _slotSize;
    int _top;

public:

    LuaStack(LuaValue slots[], int slotSize, int top) :
        _slots(slots), _slotSize(slotSize), _top(top) { }

    static LuaStack* NewLuaStack(int size) {
        return new LuaStack(new LuaValue[size], size, 0);
    }

    void check(int n) {
        int free = _slotSize - _top;
        if(n <= free) return;

        LuaValue* newSlots = new LuaValue[_top + n];
        _slotSize = _top + n;
        memcpy(newSlots, _slots, _top * sizeof(LuaValue));
        delete[] _slots;
        _slots = newSlots;
    }

    void push(LuaValue val) {
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
    

};

#endif //LUA5_3_DECOMPILER_LUA_STACK_HPP
