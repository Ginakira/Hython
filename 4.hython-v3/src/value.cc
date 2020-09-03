/************************************************************
    File Name : value.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/03 10:02:50
************************************************************/

#include "../include/value.h"

namespace haizei {

IntValue::IntValue(int val) : BaseValue(val) {}
FloatValue::FloatValue(double val) : BaseValue(val) {}
StringValue::StringValue(std::string val) : BaseValue(val) {}

bool StringValue::isTrue() {
    if (val == "") return false;
    return true;
}

SIValue HZNULL = std::make_shared<IntValue>();

}  // namespace haizei