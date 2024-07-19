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

