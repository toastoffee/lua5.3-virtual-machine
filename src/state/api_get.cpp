/**
  ******************************************************************************
  * @file           : api_get.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/19
  ******************************************************************************
  */

#include "../api/lua_state.hpp"

void LuaState::CreateTable() {
    LuaTable t;
    _stack->Push(LuaValue(t));
}

void LuaState::NewTable() {
    CreateTable();
}

LuaType LuaState::GetTable(int idx) {
    LuaValue t = _stack->Get(idx);
    LuaValue k = _stack->Pop();

    return getTable(t, k);
}

LuaType LuaState::getTable(LuaValue t, LuaValue k) {
    assert(t.GetType() == typeid(LuaTable).name() && "not a table!");

    LuaValue v = t.GetVal<LuaTable>().Get(k);
    _stack->Push(v);
    return v.TypeOf(v);
}

LuaType LuaState::GetField(int idx, std::string k) {
    LuaValue t = _stack->Get(idx);
    return getTable(t, LuaValue(k));
}

LuaType LuaState::GetI(int idx, int64 i) {
    LuaValue t = _stack->Get(idx);
    return getTable(t, LuaValue(i));
}

void LuaState::SetTable(int idx) {
    auto t = _stack->Get(idx);
    auto v = _stack->Pop();
    auto k = _stack->Pop();

    setTable(t, k, v);
}

void LuaState::setTable(LuaValue t, LuaValue k, LuaValue v) {
    assert(t.GetType() == typeid(LuaTable).name() && "not a table!");

    t.GetVal<LuaTable>().Put(k ,v);
}

void LuaState::SetField(int idx, std::string k) {
    auto t = _stack->Get(idx);
    auto v = _stack->Pop();
    setTable(t, LuaValue(k), v);
}

void LuaState::SetI(int idx, int64 i) {
    auto t = _stack->Get(idx);
    auto v = _stack->Pop();
    setTable(t, LuaValue(i), v);
}
