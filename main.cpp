#include "main.h"
#include "nodes/node.h"

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
    outStream.open("tree.dot", std::ios::out);
    int count = 0;
    outStream << "digraph {" << std::endl;
    root->generate_tree(count, &outStream);
    outStream << "}" << std::endl;
    outStream.close();

    // print AST in cmd
    std::cout << "Built a parse-tree:" << std::endl;
    root->print_tree();

    // generate AST.txt
    std::ofstream outStream2;
    outStream2.open("tree.txt", std::ios::out);
    outStream2 << "Generate a parse-tree.txt:" << std::endl;
    root->save_tree(&outStream2);
    outStream2.close();

    //Build symbol table
    //ST st;
    //root->buildST(st);

    //Semantic analysis
    //root->checkSemantics(st);
    return 0;
}