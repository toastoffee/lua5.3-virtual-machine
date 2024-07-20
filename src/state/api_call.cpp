/**
  ******************************************************************************
  * @file           : api_call.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/20
  ******************************************************************************
  */

#include "../api/lua_state.hpp"
#include "../binChunk/chunk_reader.hpp"
#include "../vm/opcodes.hpp"

int LuaState::Load(byte chunk[], std::string chunkName, std::string mode) {

    Prototype proto = UnDump(chunk);
    Closure c{.prototype = proto};

    _stack->Push(LuaValue(c));
    return 0;
}

void LuaState::Call(int nArgs, int nResults) {
    LuaValue val = _stack->Get(-(nArgs + 1));
    Closure c = val.GetVal<Closure>();

    assert(val.GetType() == typeid(Closure).name() && "not a functions!");

    printf("call %s<%d,%d>\n", c.prototype.source.c_str(),
           c.prototype.lineDefined, c.prototype.lastLineDefined);

    CallLuaClosure(nArgs, nResults, &c);
}

void LuaState::CallLuaClosure(int nArgs, int nResults, Closure *c) {
    int nRegs = (int) c->prototype.maxStackSize;
    int nParams = (int) c->prototype.numParams;
    bool isVararg = c->prototype.isVararg == 1;

    LuaStack* newStack = LuaStack::NewLuaStack(nRegs + 20);
    newStack->_closure = c;

    auto funcAndArgs = _stack->PopN(nArgs + 1);
    funcAndArgs.erase(funcAndArgs.begin());
    newStack->PushN(funcAndArgs, nParams);
    newStack->_top = nArgs;
    if(nArgs > nParams && isVararg) {
        for (int i = 0; i < nParams; ++i) {
            funcAndArgs.erase(funcAndArgs.begin());
        }
        newStack->_varargs = funcAndArgs;
    }

    PushLuaStack(newStack);
    runLuaClosure();
    PopLuaStack();

    if(nResults != 0) {
        auto results = newStack->PopN(newStack->_top - nRegs);
        _stack->Check(results.size());
        _stack->PushN(results, nResults);
    }
}

void LuaState::runLuaClosure() {
    for (;true;) {
        Instruction inst = Fetch();
        Execute(inst, *this);
        if(GetOpcode(inst) == OP_RETURN) {
            break;
        }
    }
}