#ifndef NODES_H
#define NODES_H

/*
 * Include all head files in the "ast" folder.
 * "parser.yy" needs this file.
 */
#include "formal_parameter_list.h"
#include "goal.h"
#include "identifier.h"
#include "main_class.h"
#include "method_body.h"
#include "node.h"
#include "return.h"
#include "type.h"

#include "ast/declarations/class_declaration.h"
#include "ast/declarations/class_extends_declaration.h"
#include "ast/declarations/declarations.h"
#include "ast/declarations/variable_declaration.h"
#include "ast/declarations/method_declaration.h"

#include "ast/expressions/expression.h"
#include "ast/expressions/expression_list.h"
#include "ast/expressions/logic_expression.h"
#include "ast/expressions/compare_expression.h"
#include "ast/expressions/arith_expression.h"
#include "ast/expressions/array_search_expression.h"
#include "ast/expressions/array_length_expression.h"
#include "ast/expressions/primary_expression.h"
#include "ast/expressions/array_alloc_expression.h"
#include "ast/expressions/alloc_expression.h"
#include "ast/expressions/unary_expression.h"

#include "ast/statements/statement.h"
#include "ast/statements/assign_statement.h"
#include "ast/statements/array_assign_statement.h"
#include "ast/statements/if_statement.h"
#include "ast/statements/else_statement.h"
#include "ast/statements/while_statement.h"
#include "ast/statements/print_statement.h"

#endif