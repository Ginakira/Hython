/************************************************************
    File Name : master.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/02 10:09:16
    Desc: 实现具体责任链节点的逻辑
************************************************************/

#ifndef _MASTER_H
#define _MASTER_H

#include <memory>

#include "./AST.h"
#include "./parameter.h"
#include "./value.h"

namespace haizei {
class IMaster {
   public:
    virtual SIValue run(ASTNode &, std::shared_ptr<Parameter> &) = 0;
};

class ExprMaster : public IMaster {
   public:
    SIValue run(ASTNode &, std::shared_ptr<Parameter> &);
};
class ControlBlockMaster : public IMaster {
   public:
    SIValue run(ASTNode &, std::shared_ptr<Parameter> &);
};
class ControlNoBlockMaster : public IMaster {
   public:
    SIValue run(ASTNode &, std::shared_ptr<Parameter> &);
};
class PrintMaster : public IMaster {
   public:
    SIValue run(ASTNode &, std::shared_ptr<Parameter> &);
};
}  // namespace haizei

#endif