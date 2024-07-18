/**
  ******************************************************************************
  * @file           : inst.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/16
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_INST_H
#define LUA5_3_DECOMPILER_INST_H

#include "../state/lua_value.hpp"
#include "../api/lua_state.hpp"

#include "instruction_types.hpp"
#include "instruction_decode.hpp"

typedef LuaState LuaVM;

class Inst {

public:
    static void Move(Instruction i, LuaVM& vm);
    static void Jmp(Instruction i, LuaVM& vm);

    static void LoadNil(Instruction i, LuaVM& vm);
    static void LoadBool(Instruction i, LuaVM& vm);
    static void LoadK(Instruction i, LuaVM& vm);
    static void LoadKx(Instruction i, LuaVM& vm);

    static void Add(Instruction i, LuaVM& vm);
    static void Sub(Instruction i, LuaVM& vm);
    static void Mul(Instruction i, LuaVM& vm);
    static void Mod(Instruction i, LuaVM& vm);
    static void Pow(Instruction i, LuaVM& vm);
    static void Div(Instruction i, LuaVM& vm);
    static void Idiv(Instruction i, LuaVM& vm);
    static void Band(Instruction i, LuaVM& vm);
    static void Bor(Instruction i, LuaVM& vm);
    static void Bxor(Instruction i, LuaVM& vm);
    static void Shl(Instruction i, LuaVM& vm);
    static void Shr(Instruction i, LuaVM& vm);
    static void Unm(Instruction i, LuaVM& vm);
    static void Bnot(Instruction i, LuaVM& vm);

    static void Len(Instruction i, LuaVM& vm);
    static void Concat(Instruction i, LuaVM& vm);

    static void Eq(Instruction i, LuaVM& vm);
    static void Lt(Instruction i, LuaVM& vm);
    static void Le(Instruction i, LuaVM& vm);

    static void Not(Instruction i, LuaVM& vm);
    static void TestSet(Instruction i, LuaVM& vm);
    static void Test(Instruction i, LuaVM& vm);

    static void ForPrep(Instruction i, LuaVM& vm);
    static void ForLoop(Instruction i, LuaVM& vm);

};

void Inst::Move(Instruction i, LuaVM& vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;
    vm.Copy(b, a);
}

void Inst::Jmp(Instruction i, LuaVM& vm) {
    int a, sbx;
    AsBx(i, a, sbx);
    vm.AddPC(sbx);

    assert(a == 0 && "todo!");
}


void Inst::LoadNil(Instruction i, LuaVM& vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;

    vm.PushNil();
    for (int j = a; j < a+b; ++j) {
        vm.Copy(-1, j);
    }
    vm.Pop(1);
}

void Inst::LoadBool(Instruction i, LuaVM& vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    vm.PushBoolean(b != 0);
    vm.Replace(a);
    if(c != 0) {
        vm.AddPC(1);
    }
}

void Inst::LoadK(Instruction i, LuaVM& vm) {
    int a, bx;
    ABx(i, a, bx);
    a += 1;

    vm.GetConst(bx);
    vm.Replace(a);
}

void Inst::LoadKx(Instruction i, LuaVM& vm) {
    int a, _;
    ABx(i, a, _);
    a += 1;

    int ax;
    Ax(vm.Fetch(),ax);

    vm.GetConst(ax);
    vm.Replace(a);
}


void _binaryArith(Instruction i, LuaVM& vm, ArithOp op) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

//    vm.GetRK(b);
//    vm.GetRK(c);  // 为啥是反着的呢？？？？


    vm.GetRK(c);
    vm.GetRK(b);

    vm.Arith(op);
    vm.Replace(a);
}

void _unaryArith(Instruction i, LuaVM& vm, ArithOp op) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;

    vm.PushValue(b);
    vm.Arith(op);
    vm.Replace(a);
}

void Inst::Add(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPADD); }
void Inst::Sub(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPSUB); }
void Inst::Mul(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPMUL); }
void Inst::Mod(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPMOD); }
void Inst::Pow(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPPOW); }
void Inst::Div(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPDIV); }
void Inst::Idiv(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPIDIV); }
void Inst::Band(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPBAND); }
void Inst::Bor(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPBOR); }
void Inst::Bxor(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPBXOR); }
void Inst::Shl(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPSHL); }
void Inst::Shr(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPSHR); }
void Inst::Unm(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPUNM); }
void Inst::Bnot(Instruction i, LuaVM& vm) { _binaryArith(i, vm, LUA_OPBNOT); }

void _len(Instruction i, LuaVM& vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;

    vm.Len(b);
    vm.Replace(a);
}

void Inst::Len(Instruction i, LuaVM& vm) {
    _len(i, vm);
}

void Inst::Concat(Instruction i, LuaVM& vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;
    b += 1;
    c += 1;

    int n = c - b + 1;
    vm.CheckStack(n);
    for (int j = 0; j < b; ++j) {
        vm.PushValue(j);
    }

    vm.Concat(n);
    vm.Replace(a);
}

void _compare(Instruction i, LuaVM& vm, CompareOp op) {
    int a, b, c;
    ABC(i, a, b, c);
    vm.GetRK(b);
    vm.GetRK(c);
    if(vm.Compare(-2, -1, op) != (a != 0)) {
        vm.AddPC(1);
    }
    vm.Pop(2);
}

void Inst::Eq(Instruction i, LuaVM &vm) {
    _compare(i, vm, LUA_OPEQ);
}

void Inst::Lt(Instruction i, LuaVM &vm) {
    _compare(i, vm, LUA_OPLT);
}

void Inst::Le(Instruction i, LuaVM &vm) {
    _compare(i, vm, LUA_OPLE);
}

void Inst::Not(Instruction i, LuaVM &vm) {
    int a, b, _;
    ABC(i, a, b, _);
    a += 1;
    b += 1;

    vm.PushBoolean(!vm.ToBoolean(b));
    vm.Replace(a);
}

void Inst::TestSet(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;
    b += 1;

    if(vm.ToBoolean(b) == (c!=0)) {
        vm.Copy(b, a);
    } else {
      vm.AddPC(1);
    }
}

void Inst::Test(Instruction i, LuaVM &vm) {
    int a, _, c;
    ABC(i, a, _, c);
    a += 1;

    if(vm.ToBoolean(a) != (c != 0)) {
        vm.AddPC(1);
    }
}

void Inst::ForPrep(Instruction i, LuaVM &vm) {
    int a, sbx;
    AsBx(i, a, sbx);
    a += 1;

    // R(A) -= R(A+2)
    vm.PushValue(a);
    vm.PushValue(a + 2);
    vm.Arith(LUA_OPSUB);
    vm.Replace(a);

    // pc += sbx
    vm.AddPC(sbx);
}

void Inst::ForLoop(Instruction i, LuaVM &vm) {
    int a, sbx;
    AsBx(i, a, sbx);
    a += 1;

    // R(A) += R(A+2)
    vm.PushValue(a + 2);
    vm.PushValue(a);
    vm.Arith(LUA_OPADD);
    vm.Replace(a);

    // R(A) <?= R(A+1)
    bool isPositiveStep = vm.ToNumber(a+2) >= 0;
    if(isPositiveStep && vm.Compare(a, a+1, LUA_OPLE) ||
        !isPositiveStep && vm.Compare(a+1, a, LUA_OPLE)) {
        vm.AddPC(sbx);
        vm.Copy(a, a+3);
    }

}


#endif //LUA5_3_DECOMPILER_INST_H