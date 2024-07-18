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

#include <map>

struct LuaTable {
private:
    LuaValue *_arr;
    std::map<LuaValue, LuaValue> _map;

    LuaTable(int nArr, int nRec) {
        if(nArr > 0) {
            _arr = new LuaValue[nArr];
        }
    }

public:

    LuaValue Get(LuaValue val) {
        assert(val.GetType() != typeid(Nil).name() && "table index is nil!");

        auto t = val.ConvertToInteger(val);
        int idx = std::get<0>(t);
        
        if() {

        }

    }

};

#endif //LUA5_3_DECOMPILER_LUA_TABLE_HPP
