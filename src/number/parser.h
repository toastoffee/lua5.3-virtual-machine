/**
  ******************************************************************************
  * @file           : parser.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_PARSER_H
#define LUA5_3_DECOMPILER_PARSER_H

#include "../binChunk/chunk_types.hpp"

std::tuple<int64, bool> ParseInteger(std::string s);

std::tuple<float64, bool> ParseFloat(std::string s);


#endif //LUA5_3_DECOMPILER_PARSER_H
