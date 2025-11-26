#include "ast.h"
#include "ast_nodes.h"
#include "ast_rules.h"
#include "utils.h"
#include <stdlib.h>

ExecReturn exec_node(ASTNode *node) {
  if (node == NULL)
    return (ExecReturn){EXEC_FAIL, 0};

  NodeType type = node->type;

  switch (type) {
  case VAR_DECL:
    return exec_var_decl(node);
  case VAR_INIT:
    return exec_var_init(node);
  case VAR_UPDATE:
    return exec_var_update(node);
  case VAR_PRINT:
    print_var(node);
    return (ExecReturn){EXEC_OK, 0};
  case EXPR_NUM ... EXPR_VAR:
    return exec_expr_node(node->type, node);
  case NODE_LIST:
    return exec_node_list(node->data);
  case NODE_IF:
    return exec_if_node(node);
  case NODE_WHILE:
    return exec_while_node(node);
  case NODE_DO_WHILE:
    return exec_do_while_node(node);
  case NODE_FOR:
    return exec_for_node(node);
  case NODE_BREAK:
    return (ExecReturn){EXEC_BREAK, node->line};
  case NODE_CONTINUE:
    return (ExecReturn){EXEC_CONTINUE, node->line};
  case NODE_FUNC:
    return exec_func_node(node);
  }

  return (ExecReturn){EXEC_FAIL, 0};
}

void free_node(ASTNode *node) {
  NodeType type = node->type;

  switch (type) {
  case VAR_DECL ... VAR_PRINT:
    free_var_node(node);
    break;
  case EXPR_NUM ... EXPR_VAR:
    free_expr_node(node);
    break;
  case NODE_LIST:
    free_list_node(node);
    break;
  case NODE_IF:
    free_if_node(node);
    break;
  case NODE_WHILE ... NODE_DO_WHILE:
    free_while_node(node);
    break;
  case NODE_FOR:
    free_for_node(node);
    break;
  case NODE_FUNC:
    free_func_node(node);
    break;
  }
}
