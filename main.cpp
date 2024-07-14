#include <iostream>
#include <string>

#include "src/chunk_types.hpp"
#include "src/chunk_reader.hpp"
#include "src/chunk_log.hpp"
#include "src/lua_value.hpp"

int main() {

    FILE* file = fopen("../lua_tests/luac.out", "rb");

    if(!file) {
        assert(false && "failed to open file.");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = new char[fileSize];

    fread(source, sizeof(byte), fileSize, file);
    fclose(file);


//    Prototype p = UnDump((byte*)source);
//    ListChunk(&p);


    return 0;
}
