#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef enum {
  // Variáveis
  VAR_DECL,
  VAR_INIT,
  VAR_UPDATE,
  VAR_PRINT,

  // Expressões com um só argumento
  EXPR_NUM,
  EXPR_CHAR,
  EXPR_VAR,

  // Expressões com dois argumentos
  EXPR_PLUS,
  EXPR_MINUS,
  EXPR_TIMES,
  EXPR_DIV,
  EXPR_EQUAL,
  EXPR_NEQUAL,
  EXPR_MOD,
  EXPR_NEG,
  EXPR_EQ,
  EXPR_NE,
  EXPR_LT,
  EXPR_GT,
  EXPR_LE,
  EXPR_GE,
  EXPR_AND,
  EXPR_OR,
  EXPR_NOT,

  // Expressão com parenteses
  EXPR_PAR,

  // Expressões unárias
  EXPR_INC_PREV,
  EXPR_INC_POST,
  EXPR_DEC_PREV,
  EXPR_DEC_POST,

  // Nó com lista de nós
  NODE_LIST,

  // Nó if
  IF_STMT,
} NodeType;

typedef struct {
  NodeType type;
  void *data;
} ASTNode;

extern double exec_node(ASTNode *node);
extern void free_node(ASTNode *node);
extern ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body,
                               ASTNode *else_body);
extern void free_if_node(ASTNode *node);

#endif