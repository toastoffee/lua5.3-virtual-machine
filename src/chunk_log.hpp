/**
  ******************************************************************************
  * @file           : chunk_log.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/13
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_CHUNK_LOG_HPP
#define LUA5_3_DECOMPILER_CHUNK_LOG_HPP

#include "chunk_types.hpp"

void PrintHeader(Prototype* prototype) {
    const char* funcType = "main";
    if(prototype->lineDefined > 0) { funcType = "function"; }

    const char* varargFlag = "";
    if(prototype->isVararg > 0) { varargFlag = "+"; }

    printf("\n%s <%s:%d,%d> (%d instructions)\n",
           funcType, prototype->source.c_str(), prototype->lineDefined,prototype->lastLineDefined, (int)prototype->code.size());

    printf("%d%s params, %d slots, %d upValues, ",
           prototype->numParams, varargFlag, prototype->maxStackSize, (int)prototype->upValues.size());

    printf("%d locals, %d constants, %d functions\n",
           (int)prototype->locVars.size(), (int)prototype->constants.size(), (int)prototype->prototypes.size());
}

void PrintCode(Prototype* p) {
    printf("functions\n");
    size_t codeCount = p->code.size();

    for (int i = 0; i < codeCount; ++i) {
        printf("\t%d\t[%d]\t0x%08x\n", i+1, p->lineInfos[i], p->code[i]);
    }
}

void PrintConstants(Prototype* p) {
    size_t constantCount = p->constants.size();
    printf("constants (%d):\n", (int)constantCount);

    for (int i = 0; i < constantCount; ++i) {
        std::string s = p->constants[i].GetString();
        printf("\t%d\t%s\n", i+1, s.c_str());
    }
}

void PrintLocVars(Prototype* p) {
    size_t locVarCount = p->locVars.size();
    printf("locals (%d):\n", (int)locVarCount);

    for (int i = 0; i < locVarCount; ++i) {
        printf("\t%d\t%s\t%d\t%d\n",
               i, p->locVars[i].varName.c_str(), p->locVars[i].startPc+1, p->locVars[i].endPc+1);
    }
}

void PrintUpValue(Prototype* p) {
    size_t upValuesCount = p->upValues.size();
    printf("upvalues (%d):\n", (int)upValuesCount);

    for (int i = 0; i < upValuesCount; ++i) {
        printf("\t%d\t%s\t%d\t%d\n",
               i, p->upValueNames[i].c_str(), p->upValues[i].instack, p->upValues[i].idx);
    }
}

void ListChunk(Prototype* prototype) {
    PrintHeader(prototype);
    PrintCode(prototype);
    PrintConstants(prototype);
    PrintLocVars(prototype);
    PrintUpValue(prototype);
}

#endif //LUA5_3_DECOMPILER_CHUNK_LOG_HPP
