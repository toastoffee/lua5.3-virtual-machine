/**
  ******************************************************************************
  * @file           : lua_vm.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_VM_HPP
#define LUA5_3_DECOMPILER_LUA_VM_HPP

#include "../state/lua_state.hpp"
#include "../vm/instruction_types.hpp"


class LuaVM {
private:
    LuaState _luaState;

public:
    int PC();                   // get current pc
    void AddPC(int n);          // modify pc (to realize JMP)
    Instruction Fetch();        // fetch current instruction, make pc point to next instruction
    void GetConst(int idx);     // push current const to stack
    void GetRK(int rk);         // push current const or stack value to stack
};


#endif //LUA5_3_DECOMPILER_LUA_VM_HPP
