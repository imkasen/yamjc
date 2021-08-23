#include "ast/declarations.h"

Declarations::Declarations() : Node() {}
Declarations::Declarations(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
