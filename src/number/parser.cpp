/**
  ******************************************************************************
  * @file           : parser.cpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/15
  ******************************************************************************
  */



#include "parser.h"

std::tuple<int64, bool> ParseInteger(std::string s) {
    try {
        int64 n = std::stoi(s);
        return std::make_tuple(n, true);
    } catch (std::invalid_argument &e) {
        return std::make_tuple(0, false);
    }
}

std::tuple<float64, bool> ParseFloat(std::string s) {
    try {
        float64 d = std::stod(s);
        return std::make_tuple(d, true);
    } catch (std::invalid_argument &e) {
        return std::make_tuple(0, false);
    }
}
