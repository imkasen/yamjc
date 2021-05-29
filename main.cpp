#include "main.h"
#include "ast/node.h"

extern std::shared_ptr<Node> root;

void yy::parser::error(const string &err)
{
    std::cerr << "Cannot generate a syntax tree for this input: " << err << std::endl;
}

int main(int argc, char* argv[])
{
    // read file from cmd
    if (argc > 1)
    {
        FILE *file = std::fopen(argv[1], "r");
        if (file)
            yyin = file;
        else
            yyin = stdin;

        yy::parser parser;
        parser.parse();
        std::fclose(file);
    }

    // generate AST.dot
    std::ofstream outStream;
    outStream.open("ast.dot", std::ios::out);
    int count = 0;
    outStream << "digraph {" << std::endl;
    root->generateAST(count, &outStream);
    outStream << "}" << std::endl;
    outStream.close();

    // print AST in cmd
    // std::cout << "Built a parse-tree:" << std::endl;
    // root->printAST();

    // generate AST.txt
    std::ofstream outStream2;
    outStream2.open("ast.txt", std::ios::out);
    outStream2 << "Built a parse-tree in text:" << std::endl;
    root->saveAST(&outStream2);
    outStream2.close();

    //Build symbol table
    //ST st;
    //root->buildST(st);

    //Semantic analysis
    //root->checkSemantics(st);
    return 0;
}