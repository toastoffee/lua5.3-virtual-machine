#include <iostream>
#include <string>

#include "src/binChunk/chunk_types.hpp"
#include "src/binChunk/chunk_log.hpp"
#include "src/binChunk/chunk_reader.hpp"

#include "src/state/lua_state.hpp"


#include <algorithm>

int main() {

    // 1. test unDump
//    FILE* file = fopen("../lua_tests/luac.out", "rb");
//
//    if(!file) {
//        assert(false && "failed to open file.");
//    }
//
//    fseek(file, 0, SEEK_END);
//    long fileSize = ftell(file);
//    fseek(file, 0, SEEK_SET);
//
//    char* source = new char[fileSize];
//
//    fread(source, sizeof(byte), fileSize, file);
//    fclose(file);
//
//    Prototype p = UnDump((byte*)source);
//    ListChunk(&p);

    // 2. test lua state
//    LuaState ls;
//    ls.PushBoolean(true);    ls.PrintStack();
//    ls.PushInteger(10);      ls.PrintStack();
//    ls.PushNil();               ls.PrintStack();
//    ls.PushString("hello");  ls.PrintStack();
//    ls.PushValue(-4);       ls.PrintStack();
//    ls.Replace(3);          ls.PrintStack();
//    ls.SetTop(6);           ls.PrintStack();
//    ls.Remove(-3);          ls.PrintStack();
//    ls.SetTop(-5);          ls.PrintStack();

    // 5.4 test calc
    LuaState ls;
    ls.PushInteger(1);
    ls.PushString("2.0");
    ls.PushString("3.0");
    ls.PushNumber(4.0);
    ls.PrintStack();

    ls.Arith(LUA_OPADD);    ls.PrintStack();
    ls.Arith(LUA_OPBNOT);   ls.PrintStack();
    ls.Len(2);              ls.PrintStack();
    ls.Concat(3);            ls.PrintStack();
    ls.PushBoolean(ls.Compare(1, 2, LUA_OPEQ));
    ls.PrintStack();

    return 0;
}
