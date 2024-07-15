/**
  ******************************************************************************
  * @file           : chunk_reader.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/13
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_CHUNK_READER_HPP
#define LUA5_3_DECOMPILER_CHUNK_READER_HPP

#include "chunk_types.hpp"

class ChunkReader {
private:
    byte* _data;

private:

    /*
     * reading of basic types
     */
    byte ReadByte() {
        byte b = *_data;
        _data += 1;
        return b;
    }

    uint32 ReadUint32() {
        uint32 u;
        memcpy(&u, _data, sizeof(uint32));
        _data += sizeof(uint32);
        return u;
    }

    uint64 ReadUint64() {
        uint64 u;
        memcpy(&u, _data, sizeof(uint64));
        _data += sizeof(uint64);
        return u;
    }

    int64 ReadLuaInteger() {
        int64 i;
        memcpy(&i, _data, sizeof(int64));
        _data += sizeof(int64);
        return i;
    }

    float64 ReadLuaNumber() {
        float64 f;
        memcpy(&f, _data, sizeof(float64));
        _data += sizeof(float64);
        return f;
    }

    byte* ReadBytes(int n) {
        byte* bytes = new byte[n];
        memcpy(bytes, _data, n);
        _data += n;
        return bytes;
    }

    std::string ReadString() {
        uint8 size = ReadByte();

        if(size == 0) {
            return "";
        }

        if(size == 0xff) {
            size = (uint8) ReadUint64();
        }

        char* c_str = new char[size];
        memcpy(c_str, _data, size-1);
        _data += (size-1);
        c_str[size-1] = '\0';
        std::string str = c_str;

        delete[] c_str;
        return str;
    }

    /*
     * read of structs
     */
    Constant ReadConstant() {
        switch(ReadByte()){
            case TAG_NIL: {
                return {TAG_NIL};
            }
            case TAG_BOOLEAN:{
                bool b = ReadByte() != 0;
                return {TAG_BOOLEAN, b};
            }
            case TAG_INTEGER:{
                int64 i = ReadLuaInteger();
                return{TAG_INTEGER, i};
            }
            case TAG_NUMBER:{
                float64 d = ReadLuaNumber();
                return{TAG_NUMBER, d};
            }
            case TAG_SHORT_STR:{
                std::string s = ReadString();
                return{TAG_SHORT_STR, s};
            }
            case TAG_LONG_STR:{
                std::string s = ReadString();
                return{TAG_LONG_STR, s};
            }
            default:
                assert(false && "corrupted!");
        }
    }

    std::vector<uint32> ReadCode() {
        uint32 size = ReadUint32();
        std::vector<uint32> code(size, 0);

        for (int i = 0; i < size; ++i) {
            code[i] = ReadUint32();
        }
        return code;
    }

    std::vector<Constant> ReadConstants() {
        uint32 size = ReadUint32();
        std::vector<Constant> constants(size, 0);

        for (int i = 0; i < size; ++i) {
            constants[i] = ReadConstant();
        }
        return constants;
    }

    std::vector<UpValue> ReadUpValues() {
        uint32 size = ReadUint32();
        std::vector<UpValue> upValues(size, {0, 0});

        for (int i = 0; i < size; ++i) {
            upValues[i].instack = ReadByte();
            upValues[i].idx = ReadByte();
        }
        return upValues;
    }

    std::vector<uint32> ReadLineInfos() {
        uint32 size = ReadUint32();
        std::vector<uint32> lineInfos(size, 0);

        for (int i = 0; i < size; ++i) {
            lineInfos[i] = ReadUint32();
        }
        return lineInfos;
    }

    std::vector<LocalVar> ReadLocVars() {
        uint32 size = ReadUint32();
        std::vector<LocalVar> locVars(size);

        for (int i = 0; i < size; ++i) {
            locVars[i].varName = ReadString();
            locVars[i].startPc = ReadUint32();
            locVars[i].endPc   = ReadUint32();
        }
        return locVars;
    }

    std::vector<std::string> ReadUpValueNames() {
        uint32 size = ReadUint32();
        std::vector<std::string> upValueNames(size, "");

        for (int i = 0; i < size; ++i) {
            upValueNames[i] = ReadString();
        }
        return upValueNames;
    }

    std::vector<Prototype> ReadPrototypes(std::string parentSource) {
        uint32 size = ReadUint32();
        std::vector<Prototype> prototypes(size);

        for (int i = 0; i < size; ++i) {
            prototypes[i] = ReadPrototype(parentSource);
        }
        return prototypes;
    }

public:
    explicit ChunkReader(byte* data) : _data(data) { }

    void CheckHeader() {

        assert(strcmp((char*)ReadBytes(4), LUA_SIGNATURE) == 0 && "not a precompiled chunk!");

        assert(ReadByte() == LUAC_VERSION && "version mismatch!");

        assert(ReadByte() == LUAC_FORMAT && "format mismatch!");

        assert(strcmp((char*)ReadBytes(6), LUAC_DATA) == 0 && "corrupted!");

        assert(ReadByte() == CINT_SIZE && "int size mismatch!");

        assert(ReadByte() == CSIZET_SIZE && "size_t size mismatch!");

        assert(ReadByte() == INSTRUCTION_SIZE && "instruction size mismatch!");

        assert(ReadByte() == LUA_INTEGER_SIZE && "lua_Integer size mismatch!");

        assert(ReadByte() == LUA_NUMBER_SIZE && "lua_Number size mismatch!");

        assert(ReadLuaInteger() == LUAC_INT && "endianness mismatch");

        assert(ReadLuaNumber() == LUAC_NUM && "float format mismatch!");

        // 17 + 16 = 33
    }

    void SkipUpValueNum() {
        ReadByte();
    }

    Prototype ReadPrototype(std::string parentSource = "") {
        std::string source = ReadString();

        if(source.size() == 0) {
            source = parentSource;
        }

        return Prototype{
            .source =           source,
            .lineDefined =      ReadUint32(),
            .lastLineDefined =  ReadUint32(),
            .numParams =        ReadByte(),
            .isVararg =         ReadByte(),
            .maxStackSize =     ReadByte(),
            .code =             ReadCode(),
            .constants =        ReadConstants(),
            .upValues =         ReadUpValues(),
            .prototypes =       ReadPrototypes(source),
            .lineInfos =        ReadLineInfos(),
            .locVars =          ReadLocVars(),
            .upValueNames =     ReadUpValueNames()
        };
    }
};


Prototype UnDump(byte data[]){
    ChunkReader reader(data);
    reader.CheckHeader();
    reader.SkipUpValueNum();
    Prototype proto = reader.ReadPrototype();
    return proto;
}


#endif //LUA5_3_DECOMPILER_CHUNK_READER_HPP
