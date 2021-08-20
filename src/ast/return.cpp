#include "ast/return.h"

#include <utility>

Return::Return() : Node() {}
Return::Return(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
