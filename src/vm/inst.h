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

const int LFIELDS_PER_FLUSH = 50;

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

    static void NewTable(Instruction i, LuaVM& vm);
    static void GetTable(Instruction i, LuaVM& vm);
    static void SetTable(Instruction i, LuaVM& vm);
    static void SetList(Instruction i, LuaVM& vm);

    static void Closure(Instruction i, LuaVM& vm);
    static void Call(Instruction i, LuaVM& vm);
    static void _return(Instruction i, LuaVM& vm);
    static void Vararg(Instruction i, LuaVM& vm);
    static void TailCall(Instruction i, LuaVM& vm);
    static void Self(Instruction i, LuaVM& vm);
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

    vm.GetRK(b);
    vm.GetRK(c);

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
    for (int j = b; j <= c; j++) {
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

void Inst::NewTable(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    vm.CreateTable();
    vm.Replace(a);
}

void Inst::GetTable(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;
    b += 1;

    vm.GetRK(c);
    vm.GetTable(b);
    vm.Replace(a);
}

void Inst::SetTable(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    vm.GetRK(b);
    vm.GetRK(c);
    vm.SetTable(a);
}

void Inst::SetList(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    if(c > 0) {
        c -= 1;
    } else {
        auto inst = vm.Fetch();
        Ax(inst, c);
    }

    int64 idx = c * LFIELDS_PER_FLUSH;

    for (int j = 1; j <= b; ++j) {
        idx++;
        vm.PushValue(a + j);
        vm.SetI(a, idx);
    }
}

void Inst::Closure(Instruction i, LuaVM &vm) {
    int a, bx;
    ABx(i, a, bx);
    a += 1;

    vm.LoadProto(bx);
    vm.Replace(a);
}

void _fixStack(int a, LuaVM &vm) {
    int x = (int)vm.ToInteger(-1);
    vm.Pop(1);

    vm.CheckStack(x - a);
    for (int i = a; i < x; i++) {
        vm.PushValue(i);
    }
    vm.Rotate(vm.RegisterCount() + 1, x - a);
}

int _pushFuncAndArgs(int a, int b, LuaVM &vm) {
    if(b >= 1) {
        vm.CheckStack(b);
        for (int i = a; i < a+b; i++) {
            vm.PushValue(i);
        }
        return b-1;
    } else {
        _fixStack(a, vm);
        return vm.GetTop() - vm.RegisterCount() - 1;
    }
}

void _popResults(int a, int c, LuaVM &vm) {
    if(c == 1)  {
        // no results
    } else if( c > 1) { // c-1 results
        for (int i = a + c - 2; i >= a ; i--) {
            vm.Replace(i);
        }
    } else {
        vm.CheckStack(1);
        vm.PushInteger((int64)a);
    }
}

void Inst::Call(Instruction i, LuaVM &vm) {
    int a, b, c;
    ABC(i, a, b, c);
    a += 1;

    int nArgs = _pushFuncAndArgs(a, b, vm);
    vm.Call(nArgs, c-1);
    _popResults(a, c, vm);
}

void Inst::_return(Instruction i, LuaVM &vm) {
    int a, b, _;
    ABC(i, a, b, _);

    if(b == 1) {
        // no return values
    }
    else if(b > 1) {  // b-1 return values
        vm.CheckStack(b - 1);
        for (int j = a; j <= a+b-2 ; j++) {
            vm.PushValue(j);
        }
    } else {
        _fixStack(a, vm);
    }
}

#endif //LUA5_3_DECOMPILER_INST_H
