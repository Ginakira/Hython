/************************************************************
    File Name : ExprTreeEvaluator.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 09:15:26
************************************************************/

#include "../include/ExprTreeEvaluator.h"

#include "../include/parameter.h"
#include "../include/single.h"

namespace haizei {
ExprTreeEvaluator::ExprTreeEvaluator() {}

int ExprTreeEvaluator::run(haizei::ASTNode tree) {
    std::shared_ptr<Parameter> p = std::make_shared<Parameter>(nullptr);
    return MasterChainSingle::run(tree, p);
}
}  // namespace haizei