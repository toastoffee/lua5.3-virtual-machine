/**
  ******************************************************************************
  * @file           : lua_impl.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/19
  ******************************************************************************
  */

#include "lua_table.hpp"

int LuaValue::TypeOf(LuaValue val) {
    if(val.GetType() == typeid(Nil).name()) {
        return LUA_TNIL;
    }
    else if(val.GetType() == typeid(bool).name()) {
        return LUA_TBOOLEAN;
    }
    else if(val.GetType() == typeid(int64).name()) {
        return LUA_TNUMBER;
    }
    else if(val.GetType() == typeid(float64).name()) {
        return LUA_TNUMBER;
    }
    else if(val.GetType() == typeid(std::string).name()) {
        return LUA_TSTRING;
    }
    else if(val.GetType() == typeid(LuaTable).name()) {
        return LUA_TTABLE;
    }
    else{
        assert(false && "todo!");
    }
}
