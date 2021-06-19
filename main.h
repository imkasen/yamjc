#ifndef MAIN_H
#define MAIN_H

#include "ast/node.h"
#include <iostream>
#include <string>
#include <fstream>

#include "parser.tab.hh"
#define YY_DECL yy::parser::symbol_type yylex()
YY_DECL;

using std::cout;
using std::endl;
using std::string;

#endif
