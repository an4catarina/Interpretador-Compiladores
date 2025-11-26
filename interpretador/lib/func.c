#include "func.h"
#include "error.h"
#include "utils.h"
#include "var.h"
#include <math.h>
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
  if (list == NULL)
    return;

  Param *param = list->next;

  while (param) {
    Param *current = param;
    param = param->next;

    if (current->value)
      free(current->value);

    free(current);
  }

  free(list);
}

void add_param(ParamList *list, void *value, VarType type) {
  if (list == NULL)
    return;

  Param *param = malloc(sizeof(Param));
  if (param == NULL)
    return;

  param->type = type;
  param->next = NULL;
  param->value = NULL;

  switch (type) {

  case INT:
  case FLOAT:
  case DOUBLE: {
    param->value = malloc(sizeof(double));
    if (param->value)
      *(double *)param->value = *(double *)value;
    break;
  }

  case VAR_CHAR: {
    param->value = malloc(sizeof(char));
    if (param->value)
      *(char *)param->value = (char)(*(double *)value);
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
  if (list == NULL || list->next == NULL) {
    puts("Lista de parâmetros vazia");
    exit(1);
  }

  Param *p = list->next;
  for (int i = 1; i < n; i++) {
    if (p == NULL) {
      puts("Número errado de argumentos");
      exit(1);
    }
    p = p->next;
  }

  if (p == NULL) {
    puts("Número errado de argumentos");
    exit(1);
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
    return get_var_value((char *)p->value, line);
  }

  return 0;
}

static double test_func(ParamList *list, int line);
static double pow_func(ParamList *list, int line);
static double sqrt_func(ParamList *list, int line);
static double printf_func(ParamList *list, int line);

double run_builtin_func(Builtins func, ParamList *list, int line) {
  double result = 0;

  switch (func) {
  case TEST_FUNC:
    return test_func(list, line);
  case POW_FUNC:
    return pow_func(list, line);
  case SQRT_FUNC:
    return sqrt_func(list, line);
  case PRINTF:
    return printf_func(list, line);
    break;
  }

  return result;
}

static double test_func(ParamList *list, int line) {
  for (int i = 1; i <= list->len; i++) {
    double n = get_param_value(list, i, line);
    printf("Valor do argumento: %lf\n", n);
  }

  return list->len;
}

static double pow_func(ParamList *list, int line) {
  if (list->len != 2)
    exit_with_error(WRONG_FUNC_CALL, line);

  double n = get_param_value(list, 1, line);
  double m = get_param_value(list, 2, line);

  return pow(n, m);
}

static double sqrt_func(ParamList *list, int line) {
  if (list->len != 1)
    exit_with_error(WRONG_FUNC_CALL, line);

  double n = get_param_value(list, 1, line);

  return sqrt(n);
}
static double printf_func(ParamList *list, int line) {
  if (list == NULL || list->next == NULL)
    return 0;

  Param *first = list->next;
  char *fmt = (char *)first->value;

  if (fmt == NULL) {
    fprintf(stderr, "String de formato nula em printf na linha %d\n", line);
    exit(1);
  }

  size_t len = strlen(fmt);

  int conv_count = 0;
  for (size_t i = 0; i < len; i++) {
    char c = fmt[i];

    if (c == '%') {
      if (i + 1 < len) {
        char c2 = fmt[i + 1];
        if (c2 == 'd' || c2 == 'f' || c2 == 'c') {
          conv_count++;
          i++;
        } else if (c2 == '%') {
          i++;
        } else {
        }
      }
    }
  }

  int expected_args = list->len - 1;

  if (conv_count != expected_args) {
    fprintf(stderr,
            "Número incorreto de argumentos em printf na linha %d "
            "(esperados: %d, recebidos: %d)\n",
            line, conv_count, expected_args);
    exit(1);
  }

  int p = 2;
  for (size_t i = 0; i < len; i++) {
    char c = fmt[i];

    if (c == '\\') {
      if (i + 1 >= len) {
        putchar('\\');
        break;
      }

      i++;
      char c2 = fmt[i];

      switch (c2) {
      case 'n':
        putchar('\n');
        break;
      case 't':
        putchar('\t');
        break;
      case '\\':
        putchar('\\');
        break;
      case '"':
        putchar('"');
        break;
      case '%':
        putchar('%');
        break;
      case '0':
        putchar('\0');
        break;
      default:
        putchar(c2);
        break;
      }

      continue;
    }

    if (c == '%') {
      if (i + 1 >= len) {
        putchar('%');
        break;
      }

      i++;
      char c2 = fmt[i];

      switch (c2) {
      case 'd': {
        double v = get_param_value(list, p++, line);
        printf("%d", (int)v);
        break;
      }
      case 'f': {
        double v = get_param_value(list, p++, line);
        printf("%f", v);
        break;
      }
      case 'c': {
        double v = get_param_value(list, p++, line);
        printf("%c", (char)v);
        break;
      }
      case '%':
        putchar('%');
        break;
      default:
        putchar('%');
        putchar(c2);
        break;
      }

      continue;
    }
    putchar(c);
  }

  return 0;
}
