/**
  ******************************************************************************
  * @file           : opcodes.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/18
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_OPCODES_HPP
#define LUA5_3_DECOMPILER_OPCODES_HPP

#include "inst.h"

struct Opcode {
    byte testFlag;      // operator is a test (next instruction must be a jump)
    byte setAFlag;      // instruction set register A
    byte argBMode;      // B arg mode
    byte argCMode;      // C arg mode
    byte opMode;
    const char* name;   // opcode name
    void (*instFunc)(Instruction , LuaVM&);
};


const Opcode opcodes[] = {
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "MOVE    ", Inst::Move},
        Opcode{0, 1, OpArgK, OpArgN, IABx,  "LOADK   ", Inst::LoadK},
        Opcode{0, 1, OpArgN, OpArgN, IABx,  "LOADKX  ", Inst::LoadKx},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "LOADBOOL", Inst::LoadBool},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "LOADNIL ", Inst::LoadNil},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "GETUPVAL", nullptr},
        Opcode{0, 1, OpArgU, OpArgK, IABC,  "GETTABUP", nullptr},
        Opcode{0, 1, OpArgR, OpArgK, IABC,  "GETTABLE", Inst::GetTable},
        Opcode{0, 0, OpArgK, OpArgK, IABC,  "SETTABUP", nullptr},
        Opcode{0, 0, OpArgU, OpArgN, IABC,  "SETUPVAL", nullptr},
        Opcode{0, 0, OpArgK, OpArgK, IABC,  "SETTABLE", Inst::SetTable},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "NEWTABLE", Inst::NewTable},
        Opcode{0, 1, OpArgR, OpArgK, IABC,  "SELF    ", Inst::Self},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "ADD     ", Inst::Add},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SUB     ", Inst::Sub},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "MUL     ", Inst::Mul},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "MOD     ", Inst::Mod},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "POW     ", Inst::Pow},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "DIV     ", Inst::Div},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "IDIV    ", Inst::Idiv},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BAND    ", Inst::Band},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BOR     ", Inst::Bor},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BXOR    ", Inst::Bxor},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SHL     ", Inst::Shl},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SHR     ", Inst::Shr},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "UNM     ", Inst::Unm},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "BNOT    ", Inst::Bnot},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "NOT     ", Inst::Not},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "LEN     ", Inst::Len},
        Opcode{0, 1, OpArgR, OpArgR, IABC,  "CONCAT  ", Inst::Concat},
        Opcode{0, 0, OpArgR, OpArgN, IAsBx, "JMP     ", Inst::Jmp},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "EQ      ", Inst::Eq},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "LT      ", Inst::Lt},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "LE      ",Inst::Le},
        Opcode{1, 0, OpArgN, OpArgU, IABC,  "TEST    ", Inst::Test},
        Opcode{1, 1, OpArgR, OpArgU, IABC,  "TESTSET ", Inst::TestSet},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "CALL    ", Inst::Call},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "TAILCALL", Inst::TailCall},
        Opcode{0, 0, OpArgU, OpArgN, IABC,  "RETURN  ", Inst::_return},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "FORLOOP ", Inst::ForLoop},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "FORPREP ", Inst::ForPrep},
        Opcode{0, 0, OpArgN, OpArgU, IABC,  "TFORCALL", nullptr},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "TFORLOOP", nullptr},
        Opcode{0, 0, OpArgU, OpArgU, IABC,  "SETLIST ", Inst::SetList},
        Opcode{0, 1, OpArgU, OpArgN, IABx,  "CLOSURE ", Inst::Closure},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "VARARG  ", Inst::Vararg},
        Opcode{0, 0, OpArgU, OpArgU, IAx,   "EXTRAARG", nullptr},
};

std::string GetOpName(Instruction i) {
    return opcodes[GetOpcode(i)].name;
}

byte GetOpMode(Instruction i) {
    return opcodes[GetOpcode(i)].opMode;
}

byte GetBMode(Instruction i) {
    return opcodes[GetOpcode(i)].argBMode;
}

byte GetCMode(Instruction i) {
    return opcodes[GetOpcode(i)].argCMode;
}

void Execute(Instruction i, LuaVM& vm) {
    uint32 k = GetOpcode(i);
    auto instFunc = opcodes[GetOpcode(i)].instFunc;
    assert(instFunc != nullptr && opcodes[GetOpcode(i)].name);
    instFunc(i, vm);
}


#endif //LUA5_3_DECOMPILER_OPCODES_HPP
