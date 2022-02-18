#include "ast/declarations/declarations.h"
using ast::Declarations;
using std::string;

Declarations::Declarations() : Node() {}
Declarations::Declarations(string t, string v) : Node(std::move(t), std::move(v)) {}
