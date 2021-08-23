#include "ast/return.h"

Return::Return() : Node() {}
Return::Return(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
