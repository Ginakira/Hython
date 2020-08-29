/************************************************************
    File Name : ExprTreeEvaluator.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/29 09:15:26
************************************************************/

#include "../include/ExprTreeEvaluator.h"

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
                ;
                return get_param(tree.text());
            }
            case PLUS:
                return run(tree[0]) + run(tree[1]);
            case MINUS:
                return run(tree[0]) - run(tree[1]);
            case TIMES:
                return run(tree[0]) * run(tree[1]);
            case DIV:
                return run(tree[0]) / run(tree[1]);
            case MOD:
                return run(tree[0]) % run(tree[1]);
            case BLOCK: {
                ExprTreeEvaluator new_this(this);
                for (int i = 0; i < tree.size(); ++i) {
                    new_this.run(tree[i]);
                }
                return 0;
            } break;
            case PRINT: {
                for (int i = 0; i < tree.size(); ++i) {
                    i&& std::cout << " ";
                    std::cout << run(tree[i]);
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
                        init_val = run(tree[i][0]);
                    }
                    this->def_param(var, init_val);
                }
                return init_val;
            } break;
            case ASSIGN: {
                string var(tree[0].text());
                get_param(var);
                int val = run(tree[1]);
                set_param(var, val);
                return val;
            }
            default:
                std::cout << "Unhandled token: #" << tree.type() << '\n';
                return -1;
        }
    } else {
        int r = 0;
        for (int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
        }
        return r;
    }
}