#ifndef MAIN_H
#define MAIN_H

#include "../build/parser.tab.hh"
#include "ast/node.h"
#include "st/symbol_table.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#define YY_DECL yy::parser::symbol_type yylex() 
YY_DECL;

#endif
