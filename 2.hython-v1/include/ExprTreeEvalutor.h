/************************************************************
    File Name : ExprTreeEvalutor.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 00:36:12
************************************************************/

#ifndef _EXPR_TREE_EVALUTOR_H
#define _EXPR_TREE_EVALUTOR_H

#include <map>
#include <string>

#include "./AST.h"

using std::map;
using std::string;

class ExprTreeEvaluator {
    map<string, int> memory;

   public:
    ExprTreeEvaluator() : next(nullptr) {}
    ExprTreeEvaluator(ExprTreeEvaluator* next) : next(next) {}
    int run(haizei::ASTNode);
    void def_param(string, int);
    void set_param(string, int);
    int get_param(string);
    ExprTreeEvaluator* next;
};

#endif