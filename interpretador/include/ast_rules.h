#ifndef AST_RULES_H
#define AST_RULES_H

#include "ast.h"
#include "ast_nodes.h"
#include <stdbool.h>

extern ExecReturn exec_var_decl(ASTNode *node);
extern ExecReturn exec_var_init(ASTNode *node);
extern ExecReturn exec_var_update(ASTNode *node);

extern ExecReturn exec_expr_node(NodeType type, ASTNode *node);

extern ExecReturn exec_node_list(ListNode *node);

ExecReturn exec_while_node(ASTNode *node);
ExecReturn exec_do_while_node(ASTNode *node);
ExecReturn exec_for_node(ASTNode *node);

extern ExecReturn exec_if_node(ASTNode *node);

#endif
