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
#include <vector>

struct LuaTable {
private:
//    std::vector<LuaValue> _arr;
    std::map<LuaValue, LuaValue> _map;

    LuaTable(int nRec) {
//        if(nArr > 0) {
//            _arr = std::vector<LuaValue>(nArr);
//        }
    }

public:

    LuaValue Get(LuaValue key) {
//        assert(val.GetType() != typeid(Nil).name() && "table index is nil!");
//
//        auto t = val.ConvertToInteger(val);
//        int idx = std::get<0>(t);
//
//        if(std::get<1>(t)) {
//            if(idx >= 1 && idx <= _arr.size()) {
//                return _arr[idx - 1];
//            }
//        }
//
//        return _map[val];

        assert(key.GetType() != typeid(Nil).name() && "table index is nil!");
        return _map[key];
    }

//    void _shrinkArray(LuaValue key, LuaValue val) {
//        int size = _arr.size();
//        for (int i = size; i >= 0 ; i--) {
//            if(_arr[i].GetType() == typeid(Nil).name()) {
//                _arr.pop_back();
//            }
//        }
//    }

//    void _expandArray() {
//        int size = _arr.size();
//        for (int idx = size + 1; true; idx++) {
//
//        }
//    }

    void Put(LuaValue key, LuaValue val) {
//        auto t = val.ConvertToInteger(val);
//        int idx = std::get<0>(t);
//
//        if(std::get<1>(t) && idx >= 1) {
//
//            if(idx <= _arr.size()) {
//                _arr[idx - 1] = val;
//                if(idx == _arr.size() && val.GetType() == typeid(Nil).name()) {
//                    _shrinkArray(key, val);
//                }
//                return;
//            }
//
//            if(idx == _arr.size() + 1) {
//                _map.erase(key);
//
//                if(val.GetType() != typeid(Nil).name()) {
//                    _arr.push_back(val);
//                }
//            }
//        }
//
//        if(val.GetType() != typeid(Nil).name()) {
//            _map[key] = val;
//        } else {
//            _map.erase(key);
//        }
        assert(key.GetType() != typeid(Nil).name() && "table index is nil!");
        _map[key] = val;
    }

    int Len() {
        return _map.size();
    }

};

#endif //LUA5_3_DECOMPILER_LUA_TABLE_HPP
