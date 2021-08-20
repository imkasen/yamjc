#include "main.h"
using std::size_t;
using std::cout;
using std::endl;
using std::string;

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

    // generate ast.dot
    std::ofstream ast_dot_stream;
    ast_dot_stream.open("ast.dot", std::ios::out);
    size_t ast_count = 0;
    ast_dot_stream << "digraph {" << endl;
    root->generateAST(ast_count, &ast_dot_stream);
    ast_dot_stream << "}" << endl;
    ast_dot_stream.close();

    // print AST in cmd
    // cout << "Built a parse-tree:" << endl;
    // root.printAST();

    // generate AST.txt
    std::ofstream ast_text_stream;
    ast_text_stream.open("ast.txt", std::ios::out);
    ast_text_stream << "Built a parse-tree in text:" << endl;
    root->saveAST(&ast_text_stream);
    ast_text_stream.close();

    // build symbol table, generate st.dot
    std::ofstream st_dot_stream;
    st_dot_stream.open("st.dot", std::ios::out);
    st_dot_stream << "graph {" << endl;
    root->buildST(&st_dot_stream);
    st_dot_stream << "}" << endl;
    st_dot_stream.close();

    //Semantic analysis
    //root.checkSemantics(st);
    return 0;
}