/**
  ******************************************************************************
  * @file           : api_stack.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */

#include "../api/lua_state.hpp"



int LuaState::GetTop() {
    return _stack->GetTop();
}

int LuaState::AbsIndex(int idx) {
    return _stack->AbsIndex(idx);
}

bool LuaState::CheckStack(int n) {
    _stack->Check(n);
    return true;
}

void LuaState::Pop(int n) {
    for (int i = 0; i < n; ++i) {
        _stack->Pop();
    }
}

void LuaState::Copy(int fromIdx, int toIdx) {
    LuaValue val = _stack->Get(fromIdx);
    _stack->Set(toIdx, val);
}

void LuaState::PushValue(int idx) {
    LuaValue val = _stack->Get(idx);
    _stack->Push(val);
}

void LuaState::Replace(int idx) {
    LuaValue val = _stack->Pop();
    _stack->Set(idx, val);
}

void LuaState::Insert(int idx) {
    Rotate(idx, 1);
}

void LuaState::Remove(int idx) {
    Rotate(idx, -1);
    Pop(1);
}

void LuaState::Rotate(int idx, int n) {
    int t = _stack->GetTop() - 1;
    int p = _stack->AbsIndex(idx) - 1;
    int m;
    if(n >= 0) {
        m = t - n;
    } else {
        m = p - n - 1;
    }
    _stack->Reverse(p, m);
    _stack->Reverse(m+1, t);
    _stack->Reverse(p, t);
}

void LuaState::SetTop(int idx) {
    int newTop = _stack->AbsIndex(idx);

    assert(newTop >= 0 && "stack underflow!");

    int n = _stack->GetTop() - newTop;
    if(n > 0) {
        for (int i = 0; i < n; ++i) {
            _stack->Pop();
        }
    } else if(n < 0) {
        for (int i = 0; i >n; --i) {
            _stack->Push(nil);
        }
    }
}