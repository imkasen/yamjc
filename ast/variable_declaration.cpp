#include "variable_declaration.h"

VarDeclaration::VarDeclaration() : Node() {}

VarDeclaration::VarDeclaration(std::string t, std::string v) : Node(t, v) {}
