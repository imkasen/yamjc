#ifndef MAIN_H
#define MAIN_H

#include "parser.tab.hh"
#include "ast/node.h"
#include <iostream>
#include <string>
#include <fstream>

#define YY_DECL yy::parser::symbol_type yylex() 
YY_DECL;

#endif
