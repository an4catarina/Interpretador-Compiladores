#ifndef FUNC_H
#define FUNC_H

#include "var.h"

typedef struct Param {
  void *value;
  VarType type;
  struct Param *next;
} Param;

typedef struct {
  Param *next;
  Param *last;
  int len;
} ParamList;

typedef enum {
  TEST_FUNC,
  POW_FUNC,
  SQRT_FUNC,
} Builtins;

extern ParamList *create_param_list();
extern void      add_param(ParamList *list, void *value, VarType type);
extern void      free_param_list(ParamList *list);
extern double    run_builtin_func(Builtins func, ParamList *list, int line);

extern double    get_param_value(ParamList *list, int n, int line);

#endif
