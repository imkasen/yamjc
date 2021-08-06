#ifndef MAIN_H
#define MAIN_H

#include "../parser.tab.hh"
#include "../include/ast/node.h"
#include "../include/st/symbol_table.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#define YY_DECL yy::parser::symbol_type yylex() 
YY_DECL;

#endif
