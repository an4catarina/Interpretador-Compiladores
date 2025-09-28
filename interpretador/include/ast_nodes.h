#ifndef AST_NODES_H
#define AST_NODES_H

#include "ast.h"

typedef struct {
  char *type;
  char *name;
  ASTNode *value;
} VarNode;

typedef struct op {
  ASTNode *left_expr;
  ASTNode *right_expr;
  void *value;
} ExprNode;

typedef struct list {
  ASTNode *node;
  struct list *next;
  struct list *last;
} ListNode;

extern ASTNode *current_list;

extern ASTNode *create_var_node(NodeType node_type, char *type, char *name,
                                ASTNode *value);
extern void free_var_node(ASTNode *node);

extern ASTNode *create_expr_node(NodeType type, void *value, ASTNode *left,
                                 ASTNode *right);
extern void free_expr_node(ASTNode *node);

extern ASTNode *create_node_list();
extern void add_list_node(ASTNode *node);
extern void free_list_node(ASTNode *node);
extern ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
extern void free_if_node(ASTNode *node);

typedef struct {
  ASTNode *condition;
  ASTNode *if_body;
  ASTNode *else_body;
} ASTNodeIf;

typedef struct {
  ASTNode *left;
  ASTNode *right;
} ASTNodeCondition;

#endif