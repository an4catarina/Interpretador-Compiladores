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

typedef struct WhileNode {
  struct ASTNode *condition;
  struct ASTNode *body;
} WhileNode;

typedef struct DoWhileNode {
  struct ASTNode *body;
  struct ASTNode *condition;
} DoWhileNode;

extern ASTNode *current_list;

extern ASTNode *create_var_node(NodeType node_type, char *type, char *name,
                                ASTNode *value);
                                extern void free_var_node(ASTNode *node);
                                
                                extern ASTNode *create_expr_node(NodeType type, void *value, ASTNode *left,
                                 ASTNode *right);
extern void free_expr_node(ASTNode *node);

extern ASTNode *create_while_node(ASTNode *condition, ASTNode *body);
extern void free_while_node(ASTNode *node);

extern ASTNode *create_do_while_node(ASTNode *body, ASTNode *condition);
extern void free_do_while_node(ASTNode *node);

extern ASTNode *create_node_list();
extern void add_list_node(ASTNode *node);
extern void free_list_node(ASTNode *node);

#endif