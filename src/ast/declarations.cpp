#include "ast/declarations.h"

#include <utility>

Declarations::Declarations() : Node() {}
Declarations::Declarations(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
