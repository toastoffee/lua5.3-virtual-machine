/**
  ******************************************************************************
  * @file           : lua_consts.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_CONSTS_HPP
#define LUA5_3_DECOMPILER_LUA_CONSTS_HPP


const int LUA_TNONE = -1,
          LUA_TNIL = 0,
          LUA_TBOOLEAN = 1,
          LUA_TLIGHTUSERDATA = 2,
          LUA_TNUMBER = 3,
          LUA_TSTRING = 4,
          LUA_TTABLE = 5,
          LUA_TFUNCTION = 6,
          LUA_TUSERDATA = 7,
          LUA_TTHREAD = 8;


const int LUA_OPADD = 0,     // +
          LUA_OPSUB = 1,     // -
          LUA_OPMUL = 2,     // *
          LUA_OPMOD = 3,     // %
          LUA_OPPOW = 4,     // ^
          LUA_OPDIV = 5,     // /
          LUA_OPIDIV = 6,    // //
          LUA_OPBAND = 7,    // &
          LUA_OPBOR  = 8,    // |
          LUA_OPBXOR = 9,    // ~
          LUA_OPSHL = 10,    // <<
          LUA_OPSHR = 11,    // >>
          LUA_OPUNM = 12,    // - (unary minus)
          LUA_OPBNOT = 13;   // ~”

const int LUA_OPEQ = 0,
          LUA_OPLT = 1,
          LUA_OPLE = 2;


#endif //LUA5_3_DECOMPILER_LUA_CONSTS_HPP
