/************************************************************
    File Name : AST.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/27 16:28:33
************************************************************/

#ifndef _AST_H
#define _AST_H

#include <iostream>

#include "../include/hythonLexer.h"
#include "../include/hythonParser.h"

namespace haizei {
class ASTNode {
   public:
    ASTNode(const char *file_name);
    ASTNode(pANTLR3_BASE_TREE);
    int size() const;
    std::string text();
    ASTNode operator[](int);
    bool hasToken() const;
    int type() const;
    void destroy();
    ~ASTNode();

   private:
    pANTLR3_INPUT_STREAM input;
    phythonLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phythonParser parser;
    pANTLR3_BASE_TREE tree;
    pANTLR3_COMMON_TOKEN tok;

    void init_tree(const char *file_name);
};
}  // namespace haizei

#endif