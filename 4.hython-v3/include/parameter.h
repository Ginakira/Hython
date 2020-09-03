/************************************************************
    File Name : parameter.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/02 16:20:47
    Desc: 作用域类
************************************************************/

#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <map>
#include <memory>
#include <string>

#include "./value.h"

namespace haizei {
class Parameter {
   public:
    Parameter(std::shared_ptr<Parameter> next);
    void def_param(std::string, SIValue);
    void set_param(std::string, SIValue);
    SIValue get_param(std::string);

   private:
    std::map<std::string, SIValue > memory;
    std::shared_ptr<Parameter> next;
};
}  // namespace haizei

#endif