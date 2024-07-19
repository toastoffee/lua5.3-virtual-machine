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

#include "../api/lua_consts.hpp"
#include "../binChunk/chunk_types.hpp"

#include "../number/parser.h"
#include "../number/math.h"

struct Nil{ };

class LuaValue {
private:
    void* _val;
    std::string _type;

private:
    std::tuple<int64, bool> _stringToInteger(std::string s) {
        auto t_i = ParseInteger(s);
        if(std::get<1>(t_i)) {
            return t_i;
        }
        auto t_d = ParseFloat(s);
        if(std::get<1>(t_d)) {
            return FloatToInteger(std::get<0>(t_d));
        }
        return std::make_tuple(0, false);
    }

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

    bool operator<(const LuaValue& v) const {
        return *(uint64*)_val < *(uint64*)v._val;
    }

    static LuaValue ConvertFromConst(Constant c) {
        switch (c._tag) {
            case TAG_NIL:
                return LuaValue();
                break;
            case TAG_BOOLEAN:
                return LuaValue(c._b);
                break;
            case TAG_NUMBER:
                return LuaValue(c._d);
                break;
            case TAG_INTEGER:
                return LuaValue(c._i);
                break;
            case TAG_SHORT_STR:
            case TAG_LONG_STR:
                return LuaValue(c._s);
                break;
            default:
                return LuaValue();
        }
    }

    std::string GetType() {
        return _type;
    }

    template<typename T>
    T GetVal(){
        return *(T*)_val;
    }

    template<typename T>
    T* GetPtr(){
        return (T*)_val;
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

    std::tuple<float64, bool> ConvertToFloat(LuaValue val) {
        if(val.GetType() == typeid(float64).name()) {
            return std::make_tuple(val.GetVal<float64>(), true);
        }
        else if(val.GetType() == typeid(int64).name()) {
            return std::make_tuple((float64)val.GetVal<int64>(), true);
        }
        else if(val.GetType() == typeid(std::string).name()) {
            return ParseFloat(val.GetVal<std::string>());
        }
        else{
            return std::make_tuple(0, false);
        }
    }

    std::tuple<int64 , bool> ConvertToInteger(LuaValue val) {
        if(val.GetType() == typeid(int64).name()) {
            return std::make_tuple(val.GetVal<int64>(), true);
        }
        else if(val.GetType() == typeid(float64).name()) {
            return FloatToInteger(val.GetVal<float64>());
        }
        else if(val.GetType() == typeid(std::string).name()) {
            return _stringToInteger(val.GetVal<std::string>());
        }
        else{
            return std::make_tuple(0, false);
        }
    }

    int TypeOf(LuaValue val);
};

const LuaValue nil;


#endif //LUA5_3_DECOMPILER_LUA_VALUE_HPP
