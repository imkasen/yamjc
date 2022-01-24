#ifndef NODES_H
#define NODES_H

/*
 * Include all head files in the "ast" folder.
 * "parser.yy" needs this file.
 */
#include "class_declaration.h"
#include "declarations.h"
#include "formal_parameter_list.h"
#include "goal.h"
#include "identifier.h"
#include "main_class.h"
#include "method_body.h"
#include "method_declaration.h"
#include "node.h"
#include "primary_expression.h"
#include "return.h"
#include "type.h"
#include "variable_declaration.h"

#include "ast/expressions/expression.h"

#include "ast/statements/statement.h"
#include "ast/statements/assign_statement.h"
#include "ast/statements/array_assign_statement.h"
#include "ast/statements/if_statement.h"
#include "ast/statements/else_statement.h"
#include "ast/statements/while_statement.h"
#include "ast/statements/print_statement.h"

#endif