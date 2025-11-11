#include "ast.h"
#include "ast_nodes.h"
#include "ast_rules.h"
#include "error.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

double exec_node(ASTNode *node) {
  if (node == NULL)
    return 0;

  NodeType type = node->type;
  VarNode *data = node->data;

  switch (type) {
  case VAR_DECL:
    if (exec_var_decl(data)) {
      printf("[DEBUG] Declaração de variável: %s\n", data->name);
    } else {
      exit_with_error(VAR_REDECLARATION, node->line);
    }
    break;
  case VAR_INIT:
    if (exec_var_init(data)) {
      printf("[DEBUG] Inicializando a variável: %s\n", data->name);
    } else {
      exit_with_error(VAR_REDECLARATION, node->line);
    }
    break;
  case VAR_UPDATE:
    if (exec_var_update(data)) {
      printf("[DEBUG] Atualizando valor da variável: %s\n", data->name);
    } else {
      exit_with_error(UNKNOWN_VAR, node->line);
    }
    break;
  case VAR_PRINT:
    print_var(data->name, node->line);
    break;
  case EXPR_NUM ... EXPR_DEC_POST:
    return exec_expr_node(node->type, node);
    break;
  case NODE_LIST:
    return exec_node_list(node->data);
    break;
  case NODE_IF:
    return exec_if_node(node);
    break;
  case NODE_WHILE:
    exec_while_node(node);
    break;
  case NODE_DO_WHILE:
    exec_do_while_node(node);
    break;
  case NODE_FOR:
    exec_for_node(node);
    break;
  }

  return 0;
}

void free_node(ASTNode *node) {
  NodeType type = node->type;

  switch (type) {
  case VAR_DECL ... VAR_PRINT:
    free_var_node(node);
    break;
  case EXPR_NUM ... EXPR_DEC_POST:
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
  }
}
