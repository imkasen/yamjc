#ifndef AST_NODES_H
#define AST_NODES_H

/*
 * Include all head files in the "ast" folder.
 * "parser.yy" needs this file.
 */
#include "goal.h"
#include "identifier.h"
#include "main_class.h"
#include "method_body.h"
#include "node.h"
#include "return.h"
#include "type.h"

#include "declarations/class_declaration.h"
#include "declarations/class_extends_declaration.h"
#include "declarations/declarations.h"
#include "declarations/variable_declaration.h"
#include "declarations/method_declaration.h"

#include "formal_parameters/formal_parameter_list.h"
#include "formal_parameters/formal_parameter.h"

#include "expressions/expression.h"
#include "expressions/expression_list.h"
#include "expressions/logic_expression.h"
#include "expressions/compare_expression.h"
#include "expressions/arith_expression.h"
#include "expressions/array_access_expression.h"
#include "expressions/array_length_expression.h"

#include "primary_expressions/primary_expression.h"
#include "primary_expressions/array_alloc_expression.h"
#include "primary_expressions/alloc_expression.h"
#include "primary_expressions/unary_expression.h"

#include "statements/statement.h"
#include "statements/assign_statement.h"
#include "statements/array_assign_statement.h"
#include "statements/if_statement.h"
#include "statements/else_statement.h"
#include "statements/while_statement.h"
#include "statements/print_statement.h"

#endif