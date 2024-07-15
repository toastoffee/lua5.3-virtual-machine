/**
  ******************************************************************************
  * @file           : math.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_MATH_H
#define LUA5_3_DECOMPILER_MATH_H

#include "../binChunk/chunk_types.hpp"

int64 IFloorDiv(int64 a, int64 b);

float64 FFloorDiv(float64 a, float64 b);

int64 IMod(int64 a, int64 b);

float64 FMod(float64 a, float64 b);

int64 ShiftLeft(int64 a, int64 n);

int64 ShiftRight(int64 a, int64 n);



#endif //LUA5_3_DECOMPILER_MATH_H
