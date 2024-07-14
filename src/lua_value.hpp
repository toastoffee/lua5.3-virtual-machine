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

struct Nil{ };

class LuaValue {
private:
    void* _val;
    std::string _type;
public:

    LuaValue() {
        _val = nullptr;
        _type = typeid(Nil).name();
    }

    template<typename T>
    explicit LuaValue(T val) {
        _val = new T;
        *(T*)_val = val;

        _type = typeid(val).name();
    }

    std::string GetType() {
        return _type;
    }

    template<typename T>
    T GetVal(){
        return *(T*)_val;
    }

    bool ConvertToBoolean(LuaValue val) {
        if(val.GetType() == typeid(Nil).name()) {
            return false;
        }
        else if(val.GetType() == typeid(bool).name()) {
            return val.GetVal<bool>();
        }
        else{
            return true;
        }
    }

    int TypeOf(LuaValue val) {
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
        else{
            assert(false && "todo!");
        }
    }
};

const LuaValue nil;


#endif //LUA5_3_DECOMPILER_LUA_VALUE_HPP
