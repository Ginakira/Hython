#include <cassert>

#include "./include/AST.h"
#include "./include/ExprTreeEvaluator.h"

int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);

    haizei::ExprTreeEvaluator eval;
    eval.run(tree);
    tree.destroy();
    return 0;
}