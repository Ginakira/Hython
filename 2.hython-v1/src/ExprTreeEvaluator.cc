/************************************************************
    File Name : ExprTreeEvaluator.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 09:15:26
************************************************************/

#include "../include/ExprTreeEvaluator.h"

#include "../include/handler.h"

ExprTreeEvaluator::ExprTreeEvaluator() : next(nullptr) {}
ExprTreeEvaluator::ExprTreeEvaluator(ExprTreeEvaluator* next) : next(next) {}

void ExprTreeEvaluator::def_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
#ifdef DEBUG
        for (auto x : memory) {
            std::cout << "debug log(memory) : " << x.first << " " << x.second
                      << std::endl;
        }
#endif
        throw std::runtime_error("param redefined : " + name);
    }
    memory[name] = val;
    return;
}

void ExprTreeEvaluator::set_param(string name, int val) {
    if (memory.find(name) == memory.end()) {
        if (this->next) {
            this->next->set_param(name, val);
            return;
        }
        throw std::runtime_error("undefined param : " + name);
    }
    memory[name] = val;
    return;
}

int ExprTreeEvaluator::get_param(string name) {
    if (memory.find(name) == memory.end()) {
        if (this->next) return this->next->get_param(name);
        throw std::runtime_error("undefined param : " + name);
    }
    return memory[name];
}

int ExprTreeEvaluator::run(haizei::ASTNode tree) {
    if (tree.hasToken()) {
        for (auto handler = IHandler::getInstance(); handler != nullptr;
             handler = handler->next) {
            if (handler->test(tree.type())) {
                return handler->run(tree, this);
            }
        }
        throw std::runtime_error("Unhandled token #" +
                                 std::to_string(tree.type()));
        return -1;
    } else {
        int r = 0;
        for (int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
        }
        return r;
    }
    return 0;
}