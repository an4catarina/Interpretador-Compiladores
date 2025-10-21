#include "ast.h"
#include "ast_nodes.h"
#include "ast_rules.h"
#include "meta.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

double exec_node(ASTNode *node) {
  if (node == NULL)
    return 0;

  NodeType type = node->type;

  // Executa nós do prefixo VAR
  if (type >= VAR_DECL && type <= VAR_PRINT) {
    VarNode *data = node->data;
    switch (type) {
    case VAR_DECL:
      if (exec_var_decl(data)) {
        printf("[DEBUG] Declaração de variável: %s\n", data->name);
      } else {
        fprintf(stderr, "[ERRO] Redeclaração da variável %s na linha %d\n",
                data->name, line);
        exit(1);
      }
      break;

    case VAR_INIT:
      if (exec_var_init(data)) {
        printf("[DEBUG] Inicializando a variável: %s\n", data->name);
      } else {
        fprintf(stderr, "[ERRO] Redeclaração da variável %s na linha %d\n",
                data->name, line);
        exit(1);
      }
      break;

    case VAR_UPDATE:
      if (exec_var_update(data)) {
        printf("[DEBUG] Atualizando valor da variável: %s\n", data->name);
      } else {
        fprintf(stderr, "[ERRO] Uso de variável desconhecida %s na linha %d\n",
                data->name, line);
        exit(1);
      }
      break;

    case VAR_PRINT:
      print_var(data->name);
      break;

    default:
      break;
    }
  }

  if (type >= EXPR_NUM && type <= EXPR_DEC_POST)
    return exec_expr_node(node->type, node->data);

  if (type == NODE_LIST)
    return exec_node_list(node->data);

  if (type == IF_STMT)
    return exec_if_node(node);

  return 0;
}

void free_node(ASTNode *node) {
  NodeType type = node->type;

  // Limpa nós do prefixo VAR
  if (type >= VAR_DECL && type <= VAR_PRINT)
    free_var_node(node);

  // Limpa nós do prefixo OP
  if (type >= EXPR_NUM && type <= EXPR_DEC_POST)
    free_expr_node(node);

  if (type == NODE_LIST)
    free_list_node(node);

  if (type == IF_STMT)
    free_if_node(node);
}
