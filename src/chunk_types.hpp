/**
  ******************************************************************************
  * @file           : chunk_types.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/13
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_CHUNK_TYPES_HPP
#define LUA5_3_DECOMPILER_CHUNK_TYPES_HPP

#include <cstdint>
#include <vector>
#include <string>

typedef uint8_t uint8;
typedef uint8_t byte;

typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int64_t  int64;
typedef double   float64;


const char*  LUA_SIGNATURE    = "\x1bLua";
const int    LUAC_VERSION     = 0x54;
const int    LUAC_FORMAT      = 0;
const char*  LUAC_DATA        = "\x19\x93\r\n\x1a\n";
const int    CINT_SIZE        = 4;
const int    CSIZET_SIZE      = 8;
const int    INSTRUCTION_SIZE = 4;
const int    LUA_INTEGER_SIZE = 8;
const int    LUA_NUMBER_SIZE  = 8;
const int    LUAC_INT         = 0x5678;
const double LUAC_NUM         = 370.5;

const byte TAG_NIL       = 0x00;
const byte TAG_BOOLEAN   = 0x01;
const byte TAG_NUMBER    = 0x03;
const byte TAG_INTEGER   = 0x13;
const byte TAG_SHORT_STR = 0x04;
const byte TAG_LONG_STR  = 0x14;

struct ChunkHeader {
    byte    signature[4];    // signature, magic number:0x1B4C7561
    byte    version;         // version, major_ver * 16 + minor_ver
    byte    format;          // format, 0 is official
    byte    luacData[6];     // LUAC_DATA, former 2 bytes are 0x1993(lua release year), then 0x0D, 0x0A, 0x1A, 0x0A
    byte    cintSize;        // cint size, usually 4 bytes, removed in lua 5.4
    byte    sizetSize;       // size_t size, usually 8 bytes, removed in lua 5.4
    byte    instructionSize; // lua instruction size, usually 4 bytes
    byte    luaIntegerSize;  // lua integer size, usually 8 bytes
    byte    luaNumberSize;   // lua double number size, usually 8 bytes
    int64_t luacInt;         // LUAC_INT, 0x5678(size depends on lua Integer size) to set big-end or small-end
    double  luacNum;         // LUAC_NUM, 370.5(size depends on lua double size) to check float format, usually IEEE 754
};


struct UpValue {
    byte instack;
    byte idx;
};

struct LocalVar {
    char*    varName;
    uint32_t startPc;
    uint32_t endPc;
};

struct Constant{
private:
    byte _tag;

    bool _b;
    float64 _d;
    int64 _i;
    std::string _s;
public:

    Constant(byte tag) :                _tag(tag) { }
    Constant(byte tag, bool b) :        _tag(tag), _b(b) { }
    Constant(byte tag, float64 d) :     _tag(tag), _d(d) { }
    Constant(byte tag, int64 i) :       _tag(tag), _i(i) { }
    Constant(byte tag, std::string s) : _tag(tag), _s(s) { }

    std::string GetString() {
        char *cs;
        std::string s;
        switch (_tag) {
            case TAG_NIL:
                cs = (char*)malloc(4);
                snprintf(cs, 4, "nil");
                break;
            case TAG_BOOLEAN:
                cs = (char*)malloc(4);
                snprintf(cs, 4, "%x", _b);
                break;
            case TAG_NUMBER:
                cs = (char*)malloc(16);
                snprintf(cs, 16, "%lf", _d);
                break;
            case TAG_INTEGER:
                cs = (char*)malloc(16);
                snprintf(cs, 16, "%lld", _i);
                break;
            case TAG_SHORT_STR:
            case TAG_LONG_STR:
                cs = (char*) malloc(0);
                s = '\"' + _s + '\"';
                break;
        }

        s = cs;
        delete[] cs;
        return s;
    }
};

struct Prototype {
    char*                    source;
    uint32_t                 lineDefined;
    uint32_t                 lastLineDefined;
    byte                     numParams;
    byte                     isVararg;
    byte                     maxStackSize;
    std::vector<uint32_t>    code;
    std::vector<Constant>    constants;
    std::vector<UpValue>     upValues;
    std::vector<Prototype*>  prototypes;
    std::vector<uint32_t>    lineInfos;
    std::vector<LocalVar>    locVars;
    std::vector<char*>       upValueNames;
};

struct binaryChunk {
    ChunkHeader header;
    byte        upValues_size;
    Prototype*  mainFunc;
};

#endif //LUA5_3_DECOMPILER_CHUNK_TYPES_HPP
