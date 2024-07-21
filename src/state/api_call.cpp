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

#include "../binChunk/chunk_log.hpp"

int LuaState::Load(byte chunk[], std::string chunkName, std::string mode) {

    Prototype proto = UnDump(chunk);
    Closure c{.prototype = proto};

    ListChunk(&proto);

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
    std::vector<LuaValue> vs1(funcAndArgs.begin() + 1, funcAndArgs.end());
    newStack->PushN(vs1, nParams);
    newStack->_top = nRegs;
    if(nArgs > nParams && isVararg) {
        std::vector<LuaValue> vs2(funcAndArgs.begin() + nParams + 1, funcAndArgs.end());
        newStack->_varargs = vs2;
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
        printf("\t[%02d] %s", _stack->_pc, GetOpName(inst).c_str());
        PrintTypesInverse();
        if(GetOpcode(inst) == OP_RETURN) {
            break;
        }
    }
}