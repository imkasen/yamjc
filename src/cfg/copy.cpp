#include "copy.h"
using cfg::Copy;
using std::string;

Copy::Copy() : Tac() {}
Copy::Copy(string lhs, string result) : Tac("", std::move(lhs), "", std::move(result)) {}
