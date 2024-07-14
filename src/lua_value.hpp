/**
  ******************************************************************************
  * @file           : lua_value.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_VALUE_HPP
#define LUA5_3_DECOMPILER_LUA_VALUE_HPP

#include <typeinfo>

#include "lua_consts.hpp"
#include "chunk_types.hpp"

struct nil{ };

template<typename T>
int TypeOf(T t) {
    if(typeid(t) == typeid(nil)) {
        return LUA_TNIL;
    }
    else if(typeid(t) == typeid(bool)) {
        return LUA_TBOOLEAN;
    }
    else if(typeid(t) == typeid(int64)) {
        return LUA_TNUMBER;
    }
    else if(typeid(t) == typeid(float64)) {
        return LUA_TNUMBER;
    }
    else if(typeid(t) == typeid(std::string)) {
        return LUA_TSTRING;
    }
    else{
        assert(false && "todo!");
    }
}


#endif //LUA5_3_DECOMPILER_LUA_VALUE_HPP
