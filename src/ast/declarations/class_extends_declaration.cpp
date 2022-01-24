#include "ast/declarations/class_extends_declaration.h"
using std::string;

ClassExtendsDeclaration::ClassExtendsDeclaration() : Node() {}
ClassExtendsDeclaration::ClassExtendsDeclaration(string t, string v) : Node(std::move(t), std::move(v)) {}
