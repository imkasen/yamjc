#include "main.h"
using std::size_t;
using std::cout;
using std::endl;
using std::string;

extern Node root;

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
    std::ofstream ast_dot_stream;
    ast_dot_stream.open("ast.dot", std::ios::out);
    size_t count = 0;
    ast_dot_stream << "digraph {" << endl;
    root.generateAST(count, &ast_dot_stream);
    ast_dot_stream << "}" << endl;
    ast_dot_stream.close();

    // print AST in cmd
    // cout << "Built a parse-tree:" << endl;
    // root.printAST();

    // generate AST.txt
    std::ofstream ast_text_stream;
    ast_text_stream.open("ast.txt", std::ios::out);
    ast_text_stream << "Built a parse-tree in text:" << endl;
    root.saveAST(&ast_text_stream);
    ast_text_stream.close();

    // build symbol table, generate st.dot
    std::shared_ptr<SymbolTable> st = std::shared_ptr<SymbolTable>();
    root.buildST(st);

    //Semantic analysis
    //root.checkSemantics(st);
    return 0;
}