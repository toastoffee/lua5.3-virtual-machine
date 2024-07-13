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

        if(size == 0){
            return "";
        }

        char* c_str = new char[size+1];
        memcpy(c_str, _data, size);
        _data += size;
        c_str[size] = '\0';
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
};


#endif //LUA5_3_DECOMPILER_CHUNK_READER_HPP
