#include "main.h"
#include "node.h"

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

    std::ofstream outStream;
    outStream.open("tree.dot", std::ios::out);

    std::cout << "Built a parse-tree:" << std::endl;
    root->print_tree();
    int count = 0;
    outStream << "digraph {" << std::endl;
    root->generate_tree(count, &outStream);
    outStream << "}" << std::endl;
    outStream.close();

    //Build symbol table
    //ST st;
    //root->buildST(st);

    //Semantic analysis
    //root->checkSemantics(st);
    return 0;
}