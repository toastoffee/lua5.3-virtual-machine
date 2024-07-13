#include <iostream>
#include <string>

#include "src/chunk_types.hpp"
#include "src/chunk_reader.hpp"

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

    ChunkReader reader((byte*)source);

    reader.CheckHeader();
    reader.SkipUpValueNum();
    Prototype p = reader.ReadPrototype();

    return 0;
}
