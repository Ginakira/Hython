/************************************************************
    File Name : handle.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/02 09:34:46
************************************************************/
#include "../include/handle.h"

namespace haizei {

IHandle::IHandle(IHandle *next) : __next(next){};
ExprHandle::ExprHandle(IHandle *next) : IHandle(next){};
ControlNoBlockHandle::ControlNoBlockHandle(IHandle *next) : IHandle(next){};
ControlBlockHandle::ControlBlockHandle(IHandle *next) : IHandle(next){};
PrintHandle::PrintHandle(IHandle *next) : IHandle(next){};

IHandle *IHandle::next() const { return __next; }

std::shared_ptr<IMaster> ExprHandle::getMaster() const {
    return std::make_shared<ExprMaster>();
}

std::shared_ptr<IMaster> ControlBlockHandle::getMaster() const {
    return std::make_shared<ControlBlockMaster>();
}

std::shared_ptr<IMaster> ControlNoBlockHandle::getMaster() const {
    return std::make_shared<ControlNoBlockMaster>();
}

std::shared_ptr<IMaster> PrintHandle::getMaster() const {
    return std::make_shared<PrintMaster>();
}

bool ExprHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case INT:
        case ID:
        case PLUS:
        case MINUS:
        case TIMES:
        case DIV:
        case MOD:
        case OR:
        case AND:
        case GT:
        case LITTLE:
        case EQ:
        case GE:
        case LE:
        case NE:
        case ASSIGN:
        case DEF:
            return true;
    }
    return false;
}

bool ControlBlockHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case BLOCK:
        case FOR:
            return true;
    }
    return false;
}

bool ControlNoBlockHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case IF:
        case WHILE:
        case DOWHILE:
            return true;
    }
    return false;
}

bool PrintHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case PRINT:
            return true;
    }
    return false;
}
}  // namespace haizei