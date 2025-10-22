#include "ast_nodes.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *current_list = NULL;

ASTNode *create_var_node(NodeType node_type, char *type, char *name,
                         ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  VarNode *vn = malloc(sizeof(VarNode));

  node->type = node_type;
  node->data = vn;

  if (name != NULL) {
    vn->name = malloc(strlen(name) + 1);
    strcpy(vn->name, name);
  } else {
    vn->name = NULL;
  }

  if (type != NULL) {
    vn->type = malloc(strlen(type) + 1);
    strcpy(vn->type, type);
  } else {
    vn->type = NULL;
  }

  if (value != NULL) {
    vn->value = value;
  } else {
    vn->value = NULL;
  }

  return node;
}

void free_var_node(ASTNode *node) {
  VarNode *vn = node->data;

  if (vn->name)
    free(vn->name);
  if (vn->type)
    free(vn->type);
  if (vn->value)
    free_expr_node(vn->value);

  free(vn);
  free(node);
}

ASTNode *create_expr_node(NodeType type, void *value, ASTNode *left,
                          ASTNode *right) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->data = malloc(sizeof(ExprNode));
  node->type = type;

  ExprNode *data = node->data;
  data->left_expr = left;
  data->right_expr = right;

  if (type == EXPR_NUM || type == EXPR_CHAR) {
    double *d = value;
    data->value = malloc(sizeof(double));
    memcpy(data->value, value, sizeof(double));
  } else if (type == EXPR_VAR ||
             (type >= EXPR_INC_PREV && type <= EXPR_DEC_POST)) {
    data->value = malloc(strlen(value) + 1);
    memcpy(data->value, value, strlen(value) + 1);
  }

  return node;
}

void free_expr_node(ASTNode *node) {
  ExprNode *data = node->data;

  if (data) {
    if (data->left_expr != NULL)
      free_expr_node(data->left_expr);

    if (data->right_expr != NULL)
      free_expr_node(data->right_expr);

    if (data->value != NULL)
      free(data->value);
  }
}

ASTNode *create_node_list() {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_LIST;
  node->data = malloc(sizeof(ListNode));

  ListNode *list = node->data;
  list->node = NULL;
  list->next = NULL;
  list->last = NULL;

  return node;
}

void add_list_node(ASTNode *node) {
  if (node == NULL)
    return;

  ListNode *list = current_list->data;

  if (list->node == NULL) {
    list->node = node;
  } else if (list->next == NULL) {
    ListNode *ln = malloc(sizeof(ListNode));
    list->next = ln;
    list->last = ln;

    ln->node = node;
    ln->next = NULL;
    ln->last = NULL;
  } else {
    ListNode *l = malloc(sizeof(ListNode));
    list->last->next = l;
    list->last = l;

    l->node = node;
    l->next = NULL;
    l->last = NULL;
  }
}

void free_list_node(ASTNode *node) {
  ListNode *list = node->data;

  while (list != NULL) {
    ListNode *l = list;
    list = l->next;

    if (l->node != NULL)
      free_node(l->node);
    free(l);
  }

  free(node);
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body,
                        ASTNode *else_body) {
  ASTNode *node = malloc(sizeof(ASTNode));
  if (!node)
    return NULL;

  ASTNodeIf *ifn = malloc(sizeof(ASTNodeIf));
  if (!ifn) {
    free(node);
    return NULL;
  }

  node->type = IF_STMT;
  node->data = ifn;

  ifn->condition = condition;
  ifn->if_body = if_body;
  ifn->else_body = else_body;

  return node;
}

void free_if_node(ASTNode *node) {
  if (!node)
    return;

  ASTNodeIf *ifn = (ASTNodeIf *)node->data;
  if (!ifn) {
    free(node);
    return;
  }

  free_node(ifn->condition);
  free_node(ifn->if_body);
  if (ifn->else_body)
    free_node(ifn->else_body);

  free(ifn);
  free(node);
}