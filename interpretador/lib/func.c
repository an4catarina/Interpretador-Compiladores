#include "func.h"
#include "utils.h"
#include "var.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ParamList *create_param_list() {
  ParamList *list = malloc(sizeof(ParamList));

  if (list) {
    list->next = NULL;
    list->last = NULL;
    list->len = 0;
  }

  return list;
}

void free_param_list(ParamList *list) {
  Param *param = list->next;

  while (param) {
    Param *current = param;
    param = param->next;

    free(current->value);
    free(current);
  }

  if (list)
    free(list);
}

void add_param(ParamList *list, void *value, VarType type) {
  Param *param = malloc(sizeof(Param));

  if (param == NULL)
    return;

  param->type = type;
  param->next = NULL;

  switch (type) {
  case INT ... DOUBLE: {
    param->value = malloc(sizeof(double));
    if (param->value)
      *(double *)param->value = *(double *)value;
    break;
  }
  case VAR_CHAR: {
    param->value = malloc(sizeof(char));
    if (param->value) {
      *(char *)param->value = (char)(*(double *)value);
    }
    break;
  }
  case VAR:
    param->value = value;
    break;
  }

  if (list->next == NULL) {
    list->next = param;
    list->last = param;
  } else {
    list->last->next = param;
    list->last = param;
  }

  list->len++;
}

double get_param_value(ParamList *list, int n, int line) {
  Param *p = list->next;
  for (int i = 1; i < n; i++) {
    if (p == NULL) {
      puts("Número errado de argumentos");
      exit(1);
    }
    p = p->next;
  }

  switch (p->type) {
  case INT:
    return *(int *)p->value;
  case FLOAT:
    return *(float *)p->value;
  case DOUBLE:
    return *(double *)p->value;
  case VAR_CHAR:
    return *(char *)p->value;
  case VAR:
    return get_var_value(p->value, line);
  }
}

static double test_func(ParamList *list, int line) {
  for (int i = 1; i <= list->len; i++) {
    double n = get_param_value(list, i, line);
    printf("Valor do argumento: %lf\n", n);
  }

  return list->len;
}

double run_builtin_func(Builtins func, ParamList *list, int line) {
  double result = 0;

  switch (func) {
  case TEST_FUNC:
    return test_func(list, line);
  }

  return result;
}
