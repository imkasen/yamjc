#ifndef MAIN_H
#define MAIN_H

#include <cstdio>
#include "ast/node.h"
#include "parser.tab.hh"  // ${PROJECT_BINARY_DIR}
#include "smi/interpreter.h"

#define YY_DECL yy::parser::symbol_type yylex()
YY_DECL;

#endif
