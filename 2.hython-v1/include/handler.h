/************************************************************
    File Name : handler.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 16:37:36
************************************************************/

#ifndef _HANDLER_H
#define _HANDLER_H

#include "./AST.h"
#include "./ExprTreeEvaluator.h"

class TokenHandler {
   public:
    TokenHandler *next = nullptr;
    virtual bool test(int) = 0;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) = 0;
};

class ValueHandler : public TokenHandler {
   public:
    bool test(int) override;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) override;
};

class OperatorHandler : public TokenHandler {
   public:
    bool test(int) override;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) override;
};

class FeatureHandler : public TokenHandler {
   public:
    bool test(int) override;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) override;
};

class ConditionHandler : public TokenHandler {
   public:
    bool test(int) override;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) override;
};

class ProcessControlHandler : public TokenHandler {
   public:
    bool test(int) override;
    virtual int run(haizei::ASTNode &, ExprTreeEvaluator *) override;
};

class IHandler {
   public:
    static TokenHandler *getInstance();

   private:
    static TokenHandler *handler;
    static void initHandler();
    IHandler() = default;
    IHandler(const IHandler &) = default;
    ~IHandler() = default;
};

#endif