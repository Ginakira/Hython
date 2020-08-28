#include <cassert>
#include <iostream>
#include <map>
#include <string>

#include "./include/AST.h"
#include "./include/ExprTreeEvalutor.h"
using std::cout;
using std::endl;
using std::map;
using std::string;

int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);

    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    cout << "Evaluator result: " << rr << '\n';
    tree.destroy();
    return 0;
}