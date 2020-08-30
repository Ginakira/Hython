/************************************************************
    File Name : handler.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 22:17:44
************************************************************/

#include "../include/handler.h"

#include <iostream>

#include "../include/hythonParser.h"

TokenHandler *IHandler::handler = nullptr;

TokenHandler *IHandler::getInstance() {
    if (handler == nullptr) {
        initHandler();
    }
    return handler;
}

void IHandler::initHandler() {
    ValueHandler *value_handler = new ValueHandler;
    OperatorHandler *operator_handler = new OperatorHandler;
    FeatureHandler *feature_handler = new FeatureHandler;
    ConditionHandler *condition_handler = new ConditionHandler;
    ProcessControlHandler *process_control_handler = new ProcessControlHandler;

    handler = value_handler;
    value_handler->next = operator_handler;
    operator_handler->next = feature_handler;
    feature_handler->next = condition_handler;
    condition_handler->next = process_control_handler;
    return;
}

bool ValueHandler::test(int token) {
    if (token == INT || token == ID) {
        return true;
    }
    return false;
}

bool OperatorHandler::test(int token) {
    if (token == PLUS || token == MINUS || token == TIMES || token == DIV ||
        token == MOD) {
        return true;
    }
    return false;
}

bool FeatureHandler::test(int token) {
    if (token == BLOCK || token == PRINT || token == DEF || token == ASSIGN) {
        return true;
    }
    return false;
}

bool ConditionHandler::test(int token) {
    if (token == OR || token == AND || token == GT || token == LITTLE ||
        token == EQ || token == GE || token == LE || token == NE) {
        return true;
    }
    return false;
}

bool ProcessControlHandler::test(int token) {
    if (token == IF || token == FOR || token == WHILE || token == DOWHILE) {
        return true;
    }
    return false;
}

int ValueHandler::run(haizei::ASTNode &tree, ExprTreeEvaluator *that) {
    switch (tree.type()) {
        case INT: {
            std::string s = tree.text();
            if (s[0] == '~') {
                return -atoi(s.c_str() + 1);
            } else {
                return atoi(s.c_str());
            }
        }
        case ID: {
            return that->get_param(tree.text());
        }
    }
    return 0;
}

int OperatorHandler::run(haizei::ASTNode &tree, ExprTreeEvaluator *that) {
    switch (tree.type()) {
        case PLUS:
            return that->run(tree[0]) + that->run(tree[1]);
        case MINUS:
            return that->run(tree[0]) - that->run(tree[1]);
        case TIMES:
            return that->run(tree[0]) * that->run(tree[1]);
        case DIV:
            return that->run(tree[0]) / that->run(tree[1]);
        case MOD:
            return that->run(tree[0]) % that->run(tree[1]);
    }
    return 0;
}
int FeatureHandler::run(haizei::ASTNode &tree, ExprTreeEvaluator *that) {
    switch (tree.type()) {
        case BLOCK: {
            ExprTreeEvaluator new_that(that);
            for (int i = 0; i < tree.size(); ++i) {
                new_that.run(tree[i]);
            }
            return 0;
        } break;
        case PRINT: {
            for (int i = 0; i < tree.size(); ++i) {
                i &&std::cout << " ";
                std::cout << that->run(tree[i]);
            }
            std::cout << std::endl;
            return 0;
        } break;
        case DEF: {
            int init_val = 0;
            for (int i = 0; i < tree.size(); ++i) {
                string var(tree[i].text());
                init_val = 0;
                if (tree[i].size() == 1) {
                    init_val = that->run(tree[i][0]);
                }
                that->def_param(var, init_val);
            }
            return init_val;
        } break;
        case ASSIGN: {
            string var(tree[0].text());
            that->get_param(var);
            int val = that->run(tree[1]);
            that->set_param(var, val);
            return val;
        }
    }
    return 0;
}
int ConditionHandler::run(haizei::ASTNode &tree, ExprTreeEvaluator *that) {
    switch (tree.type()) {
        case OR: {
            return that->run(tree[0]) || that->run(tree[1]);
        } break;
        case AND: {
            return that->run(tree[0]) && that->run(tree[1]);
        } break;
        case GT: {
            return that->run(tree[0]) > that->run(tree[1]);
        } break;
        case LITTLE: {
            return that->run(tree[0]) < that->run(tree[1]);
        } break;
        case EQ: {
            return that->run(tree[0]) == that->run(tree[1]);
        } break;
        case GE: {
            return that->run(tree[0]) >= that->run(tree[1]);
        } break;
        case LE: {
            return that->run(tree[0]) <= that->run(tree[1]);
        } break;
        case NE: {
            return that->run(tree[0]) != that->run(tree[1]);
        } break;
    }
    return 0;
}
int ProcessControlHandler::run(haizei::ASTNode &tree, ExprTreeEvaluator *that) {
    switch (tree.type()) {
        case IF: {
            if (that->run(tree[0])) {
                that->run(tree[1]);
            } else if (tree.size() == 3) {
                that->run(tree[2]);
            }
            return 0;
        } break;
        case FOR: {
            ExprTreeEvaluator new_that(that);
            for (new_that.run(tree[0]); new_that.run(tree[1]);
                 new_that.run(tree[2])) {
                new_that.run(tree[3]);
            }
            return 0;
        } break;
        case WHILE: {
            while (that->run(tree[0])) {
                that->run(tree[1]);
            }
            return 0;
        } break;
        case DOWHILE: {
            do {
                that->run(tree[1]);
            } while (that->run(tree[0]));
        } break;
    }
    return 0;
}