#ifndef MAIN_H
#define MAIN_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "ast/node.h"
#include "parser.tab.hh"  // ${PROJECT_BINARY_DIR}
#include "st/symbol_table.h"

#define YY_DECL yy::parser::symbol_type yylex()
YY_DECL;

#endif
