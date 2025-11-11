#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef enum
{
  // Variáveis
  VAR_DECL,
  VAR_INIT,
  VAR_UPDATE,
  VAR_PRINT,

  // Expressões com um só argumento
  EXPR_NUM,
  EXPR_CHAR,

  // Expressões com dois argumentos
  EXPR_PLUS,
  EXPR_MINUS,
  EXPR_TIMES,
  EXPR_DIV,
  EXPR_EQUAL,
  EXPR_NEQUAL,
  EXPR_MOD,
  EXPR_NEG,
  EXPR_LT,
  EXPR_GT,
  EXPR_LE,
  EXPR_GE,
  EXPR_AND,
  EXPR_OR,
  EXPR_NOT,

  // Expressão com parenteses
  EXPR_PAR,

  // Expressões com variáveis
  EXPR_INC_PREV,
  EXPR_INC_POST,
  EXPR_DEC_PREV,
  EXPR_DEC_POST,
  EXPR_VAR,

  // Nó com lista de nós
  NODE_LIST,

  // Controle de fluxo
  NODE_IF,
  NODE_WHILE,
  NODE_DO_WHILE,
  NODE_FOR,
} NodeType;

typedef enum {
  EXEC_OK,
  EXEC_FAIL,
  EXEC_BREAK,
  EXEC_CONTINUE,
} ExecStatus;

typedef struct
{
  NodeType type;
  void *data;
  int line;
} ASTNode;

typedef struct {
  ExecStatus status;
  double value;
} ExecReturn;

extern ExecReturn exec_node(ASTNode *node);
extern void free_node(ASTNode *node);
extern ASTNode *create_if_node(ASTNode *condition, ASTNode *if_body,
                               ASTNode *else_body);
extern void free_if_node(ASTNode *node);

#endif
