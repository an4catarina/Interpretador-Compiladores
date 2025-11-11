#include "utils.h"
#include "ast.h"
#include "ast_nodes.h"
#include "error.h"
#include "var.h"
#include <stdio.h>
#include <string.h>

double convert_char(char *c) {
  double value;

  if (strlen(c) == 4) {
    switch (c[2]) {
    case 'a':
      value = '\a';
      break;
    case 'b':
      value = '\b';
      break;
    case 'f':
      value = '\f';
      break;
    case 'n':
      value = '\n';
      break;
    case 'r':
      value = '\r';
      break;
    case 't':
      value = '\t';
      break;
    case 'v':
      value = '\v';
      break;
    case '0':
      value = '\0';
      break;
    default:
      value = c[2];
      break;
    }
  } else {
    value = c[1];
  }

  return value;
}

void print_var(ASTNode *node) {
  VarNode *data = node->data;
  char *name = data->name;

  Var *var = get_var(name);
  if (var != NULL) {
    VarType type = var->type;
    void *value = var->value;
    printf("[DEBUG] Variável: %s\n", var->name);
    printf("[DEBUG] Tipo: %s\n", var_type_strings[type]);

    switch (type) {
    case INT:
      int *int_value = value;
      printf("[DEBUG] Valor: %d\n", *int_value);
      break;
    case FLOAT:
      float *float_value = value;
      printf("[DEBUG] Valor: %f\n", *float_value);
      break;
    case DOUBLE:
      double *double_value = value;
      printf("[DEBUG] Valor: %lf\n", *double_value);
      break;
    case VAR_CHAR:
      char *char_value = value;
      printf("[DEBUG] Valor: '%c'\n", *char_value);
      break;
    default:
      printf("[DEBUG] Variável inválida\n");
      break;
    }
  } else {
    exit_with_error(UNKNOWN_VAR, node->line);
  }
}

double get_var_value(char *name, int line) {
  Var *var = get_var(name);
  if (var != NULL) {
    VarType type = var->type;
    void *value = var->value;
    double v;

    switch (type) {
    case INT:
      int *int_value = value;
      v = *int_value;
      break;
    case FLOAT:
      float *float_value = value;
      v = *float_value;
      break;
    case DOUBLE:
      double *double_value = value;
      v = *double_value;
      break;
    case VAR_CHAR:
      char *char_value = value;
      v = *char_value;
      break;
    }

    return v;
  } else {
    exit_with_error(UNKNOWN_VAR, line);
  }
}
