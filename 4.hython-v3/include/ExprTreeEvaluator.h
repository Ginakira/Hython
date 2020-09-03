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
#include "./value.h"

namespace haizei {
class ExprTreeEvaluator {
   public:
    ExprTreeEvaluator();
    SIValue run(haizei::ASTNode);

   private:
};
}  // namespace haizei
#endif