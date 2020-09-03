/************************************************************
    File Name : value.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/03 09:57:15
************************************************************/
#ifndef _VALUE_H
#define _VALUE_H
#include <memory>
#include <string>

namespace haizei {
class IValue {
   public:
    virtual std::string toString() = 0;
};

typedef std::shared_ptr<IValue> SIValue;

template <typename T>
class BaseValue : public IValue {
   public:
    BaseValue(const T &val) : val(val) {}
    std::string toString() override { return std::to_string(val); }
    virtual bool isTrue() {
        if (val) return true;
        return false;
    }
    bool isFalse() { return !(this->isTrue()); }

   protected:
    T val;
};

class IntValue : public BaseValue<int> {
   public:
    IntValue(int);
};
class FloatValue : public BaseValue<double> {
   public:
    FloatValue(double);
};
class StringValue : public BaseValue<std::string> {
   public:
    StringValue(std::string);
    bool isTrue() override;
};

extern SIValue HZNULL;
}  // namespace haizei

#endif