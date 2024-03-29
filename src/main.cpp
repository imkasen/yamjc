#include "main.h"
using std::cout;
using std::cerr;
using std::endl;
using std::size_t;
using std::string;

extern std::shared_ptr<ast::Node> root;

void yy::parser::error(const string &err) {
    cerr << "Cannot generate a syntax tree for this input: " << err << endl;
}

// compiler [-i] /path/file
int main(int argc, char* argv[]) {
    // Read file from cmd
    if (argc > 1) {
        FILE* file = std::fopen(argv[argc - 1], "r");
        if (!file) {
            cerr << "The file path is wrong." << endl;
            return EXIT_FAILURE;
        }
        yyin = file;

        yy::parser parser;
        parser.parse();
        std::fclose(file);
    } else {
        cerr << "No input file." << endl;
        return EXIT_FAILURE;
    }

    // Generate "ast.dot"
    std::ofstream ast_dot_stream;
    ast_dot_stream.open("ast.dot", std::ios::out);
    size_t ast_count = 0;
    ast_dot_stream << "digraph {" << endl;
    ast_dot_stream << "label=\"Abstract Syntax Tree\";" << endl;
    ast_dot_stream << "labelloc=\"t\";\n" << endl;
    root->generateAST(ast_dot_stream, ast_count);
    ast_dot_stream << "}" << endl;
    ast_dot_stream.close();

    // Print AST in cmd
    // cout << "Built a parse-tree:" << endl;
    // root->printAST();

    // Generate "ast.txt"
    /*
    std::ofstream ast_text_stream;
    ast_text_stream.open("ast.txt", std::ios::out);
    ast_text_stream << "Built a parse-tree in text:" << endl;
    root->saveAST(ast_text_stream);
    ast_text_stream.close();
    */

    // Create a symbol table, generate "st.dot"
    std::ofstream st_dot_stream;
    st_dot_stream.open("st.dot", std::ios::out);
    st_dot_stream << "graph {" << endl;
    st_dot_stream << "label=\"Symbol Table\";" << endl;
    st_dot_stream << "labelloc=\"t\";\n" << endl;
    st_dot_stream << "node [shape=box, fontname=Arial, width=5];\n" << endl;
    root->buildST(st_dot_stream);
    st_dot_stream << "}" << endl;
    st_dot_stream.close();

    // Check semantic analysis
    root->semanticAnalysis();

    // Intermediate representation, generate "cfg.dot"
    std::ofstream cfg_dot_stream;
    cfg_dot_stream.open("cfg.dot", std::ios::out);
    cfg_dot_stream << "digraph {" << endl;
    cfg_dot_stream << "label=\"Control Flow Graph\";" << endl;
    cfg_dot_stream << "labelloc=\"t\";\n" << endl;
    cfg_dot_stream << "graph [splines=ortho];" << endl;
    cfg_dot_stream << "node [shape=box];\n" << endl;
    root->buildCFG(cfg_dot_stream);
    cfg_dot_stream << "}" << endl;
    cfg_dot_stream.close();

    // Generate "rbc.class", a simplified readable Java bytecode file
    std::ofstream rbc_stream;
    rbc_stream.open("rbc.class", std::ios::out);
    root->buildRBC(rbc_stream);
    rbc_stream.close();

    if (argc == 3 && std::string(argv[1]) == "-i") {
        // Stack machine interpreter
        smi::Interpreter interpreter = smi::Interpreter(root->blk_links);
        interpreter.run("rbc.class");
    }

    return EXIT_SUCCESS;
}