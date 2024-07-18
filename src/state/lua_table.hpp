/**
  ******************************************************************************
  * @file           : lua_table.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/18
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_TABLE_HPP
#define LUA5_3_DECOMPILER_LUA_TABLE_HPP

#include "lua_value.hpp"

#include <unordered_map>

struct LuaTable {
private:
    LuaValue *_arr;
    std::unordered_map<LuaValueID, LuaValue> _map;

    LuaTable(int nArr, int nRec) {
        if(nArr > 0) {
            _arr = new LuaValue[nArr];
        }
    }

public:
    

};

#endif //LUA5_3_DECOMPILER_LUA_TABLE_HPP
