#ifndef AST_NODES_H
#define AST_NODES_H

#include "ast.h"
#include "func.h"
#include <stdbool.h>

typedef struct
{
  char *type;
  char *name;
  ASTNode *value;
} VarNode;

typedef struct op
{
  ASTNode *left_expr;
  ASTNode *right_expr;
  void *value;
  int line;
} ExprNode;

typedef struct list
{
  ASTNode *node;
  struct list *next;
  struct list *last;
} ListNode;

typedef struct
{
  ASTNode *condition;
  ASTNode *if_body;
  ASTNode *else_body;
} ASTNodeIf;

typedef struct
{
  ASTNode *left;
  ASTNode *right;
} ASTNodeCondition;

typedef struct WhileNode
{
  ASTNode *condition;
  ASTNode *body;
} WhileNode;

typedef struct
{
  ASTNode *init;
  ASTNode *condition;
  ASTNode *step;
  ASTNode *body;
} ForNode;

typedef struct
{
  Builtins func;
  ParamList *params;
} FuncNode;

// Funções VarNode
extern ASTNode *create_var_node(NodeType node_type, char *type, char *name, ASTNode *value);
extern void free_var_node(ASTNode *node);

// Funções ExprNode
extern ASTNode *create_expr_node(NodeType type, void *value, ASTNode *left, ASTNode *right);
extern void free_expr_node(ASTNode *node);

// Funções ForNode
extern ASTNode *create_for_node(ASTNode *init, ASTNode *condition, ASTNode *step, ASTNode *body);
extern void free_for_node(ASTNode *node);

// Funções WhileNode
extern ASTNode *create_while_node(ASTNode *condition, ASTNode *body, bool is_while);
extern void free_while_node(ASTNode *node);

extern ASTNode *create_break_node();
extern ASTNode *create_continue_node();

typedef struct {
  char *type;
  char *name;
  ASTNode *size_expr;
} ArrayDeclNode;

typedef struct {
  char *name;
  ASTNode *index;
  ASTNode *value;
} ArrayElemNode;

// Funções de arrays
ASTNode *create_array_decl_node(char *type, char *name, ASTNode *size_expr);
ASTNode *create_array_elem_assign_node(char *name, ASTNode *index, ASTNode *value);
ASTNode *create_array_access_node(char *name, ASTNode *index);
void free_array_decl_node(ASTNode *node);
void free_array_elem_node(ASTNode *node);

// Funções ListNode
extern ASTNode *create_node_list();
extern void add_list_node(ASTNode *list, ASTNode *node);
extern void free_list_node(ASTNode *node);

// Funções ASTNodeIf
extern ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
extern void free_if_node(ASTNode *node);

// Funções FuncNode
extern ASTNode *create_func_node(Builtins func, ParamList *params);
extern void free_func_node(ASTNode *node);

#endif
