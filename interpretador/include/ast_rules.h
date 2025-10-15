#ifndef AST_RULES_H
#define AST_RULES_H

#include "ast.h"
#include "ast_nodes.h"
#include <stdbool.h>

extern bool exec_var_decl(VarNode *node);
extern bool exec_var_init(VarNode *node);
extern bool exec_var_update(VarNode *node);

extern double exec_expr_node(NodeType type, ExprNode *node);

extern double exec_node_list(ListNode *node);

void exec_while_node(ASTNode* node);
void exec_do_while_node(ASTNode* node);

#endif