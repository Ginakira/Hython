/************************************************************
    File Name : handle.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/02 09:27:45
    Desc: 责任链模式封装
************************************************************/

#include "./AST.h"
#include "./master.h"

#ifndef _HANDLE_H
#define _HANDLE_H

namespace haizei {
class IHandle {
   public:
    IHandle(IHandle *next);
    virtual bool Test(const ASTNode &) const = 0;
    virtual std::shared_ptr<IMaster> getMaster() const = 0;
    IHandle *next() const;

   private:
    IHandle *__next;
};

class ExprHandle : public IHandle {
   public:
    ExprHandle(IHandle *);
    bool Test(const ASTNode &) const;
    std::shared_ptr<IMaster> getMaster() const;
};

class ControlNoBlockHandle : public IHandle {
   public:
    ControlNoBlockHandle(IHandle *);
    bool Test(const ASTNode &) const;
    std::shared_ptr<IMaster> getMaster() const;
};
class ControlBlockHandle : public IHandle {
   public:
    ControlBlockHandle(IHandle *);
    bool Test(const ASTNode &) const;
    std::shared_ptr<IMaster> getMaster() const;
};

class PrintHandle : public IHandle {
   public:
    PrintHandle(IHandle *);
    bool Test(const ASTNode &) const;
    std::shared_ptr<IMaster> getMaster() const;
};
}  // namespace haizei
#endif