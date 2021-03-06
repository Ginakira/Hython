/************************************************************
    File Name : AST.cc
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/08/27 16:32:02
************************************************************/
#include "../include/AST.h"

#include <string.h>

namespace haizei {
ASTNode::ASTNode(const char *file_name) { init_tree(file_name); }

ASTNode::ASTNode(const pANTLR3_BASE_TREE node) : tree(node) {
    parser = nullptr;
    tokens = nullptr;
    lex = nullptr;
    input = nullptr;
    tok = tree->getToken(tree);
}

ASTNode::~ASTNode() {}

void ASTNode::destroy() {
    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);
}

int ASTNode::size() const { return this->tree->getChildCount(tree); }

std::string ASTNode::text() {
    return std::string((char *)tree->getText(tree)->chars);
}

bool ASTNode::hasToken() const {
    if (tok) return true;
    return false;
}

int ASTNode::type() const { return tok->type; }

ASTNode ASTNode::operator[](int i) {
    if (i < 0 || i >= this->size()) {
        throw std::runtime_error("ASTNode index is out of bound");
    }
    return (pANTLR3_BASE_TREE)tree->getChild(tree, i);
}

void ASTNode::init_tree(const char *file_name) {
    input = antlr3FileStreamNew((pANTLR3_UINT8)file_name, ANTLR3_ENC_8BIT);
    lex = hythonLexerNew(input);
    tokens =
        antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
    parser = hythonParserNew(tokens);
    hythonParser_prog_return r = parser->prog(parser);
    this->tree = r.tree;
    this->tok = tree->getToken(this->tree);
    return;
};

}  // namespace haizei