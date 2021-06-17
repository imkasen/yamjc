#include "main.h"
#include "ast/node.h"

extern std::shared_ptr<Node> root;

void yy::parser::error(const string &err)
{
    std::cerr << "Cannot generate a syntax tree for this input: " << err << endl;
}

int main(int argc, char* argv[])
{
    // read file from cmd
    if (argc > 1)
    {
        FILE *file = std::fopen(argv[1], "r");
        if (file)
        {
            yyin = file;
        }
        else
        {
            std::cerr << "The file path is wrong." << endl;
            return 1;
        }

        yy::parser parser;
        parser.parse();
        std::fclose(file);
    }
    else
    {
        std::cerr << "No input file." << endl;
        return 1;
    }

    // generate AST.dot
    std::ofstream outStream;
    outStream.open("ast.dot", std::ios::out);
    int count = 0;
    outStream << "digraph {" << endl;
    root->generateAST(count, &outStream);
    outStream << "}" << endl;
    outStream.close();

    // print AST in cmd
    // cout << "Built a parse-tree:" << endl;
    // root->printAST();

    // generate AST.txt
    std::ofstream outStream2;
    outStream2.open("ast.txt", std::ios::out);
    outStream2 << "Built a parse-tree in text:" << endl;
    root->saveAST(&outStream2);
    outStream2.close();

    //Build symbol table
    //ST st;
    //root->buildST(st);

    //Semantic analysis
    //root->checkSemantics(st);
    return 0;
}