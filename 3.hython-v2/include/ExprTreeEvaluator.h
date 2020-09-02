/************************************************************
    File Name : ExprTreeEvaluator.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 09:12:51
************************************************************/

#ifndef _EXPRTREEEVALUATOR_H
#define _EXPRTREEEVALUATOR_H

#include <map>
#include <string>

#include "./AST.h"

using std::string;
using std::map;

class ExprTreeEvaluator {
   public:
    ExprTreeEvaluator();
    ExprTreeEvaluator(ExprTreeEvaluator*);
    int run(haizei::ASTNode);
    void def_param(string, int);
    void set_param(string, int);
    int get_param(string);
    ExprTreeEvaluator* next;

   private:
    map<string, int> memory;
};
#endif