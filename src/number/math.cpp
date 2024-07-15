/**
  ******************************************************************************
  * @file           : math.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */

#include <cmath>

#include "math.h"

int64 IFloorDiv(int64 a, int64 b) {
    if((a > 0 && b > 0) || (a < 0 && b < 0) || a%b == 0) {
        return a / b;
    } else {
        return a / b - 1;
    }
}

float64 FFloorDiv(float64 a, float64 b) {
    return floor(a / b);
}

int64 IMod(int64 a, int64 b) {
    return a - IFloorDiv(a, b) * b;
}

float64 FMod(float64 a, float64 b) {
    return a - floor(a / b) * b;
}

int64 ShiftLeft(int64 a, int64 n) {
    if(n >= 0) {
        return a << (uint64)n;
    } else {
        return ShiftRight(a, -n);
    }
}

int64 ShiftRight(int64 a, int64 n) {
    if(n >= 0) {
        return (int64)((uint64)a >> (uint64)n);
    } else {
        return ShiftLeft(a, -n);
    }
}

std::tuple<int64, bool> FloatToInteger(float64 f) {
    int64 i = (int64)f;
    return std::make_tuple(i, (float64)i == f);
}

