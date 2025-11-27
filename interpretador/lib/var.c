#include "var.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *var_type_strings[] = {
    [INT] = "int",
    [FLOAT] = "float",
    [DOUBLE] = "double",
    [VAR_CHAR] = "char",
    [INT_ARRAY] = "int[]",
};

VarList *create_var_list() {
  VarList *vl = malloc(sizeof(VarList));
  vl->var = NULL;
  vl->next = NULL;

  return vl;
}

void free_var_list(VarList *v) {
  while (v != NULL) {
    VarList *current = v;
    v = v->next;

    if (current->var) {
      free(current->var->name);
      free(current->var->value);
      free(current->var);
    }

    free(current);
  }
}

Var *get_var(char *name) {
  Scope *scope = current_scope;

  while (scope != NULL) {
    VarList *l = scope->var_list;

    while (l->var != NULL) {
      if (strcmp(l->var->name, name) == 0) {
        return l->var;
      }
      l = l->next;
    }

    scope = scope->bottom;
  }

  return NULL;
}

bool add_var(VarType type, char *name, void *value) {
  VarList *l = current_scope->var_list;

  while (l->var != NULL) {
    if (strcmp(l->var->name, name) == 0)
      return false;
    l = l->next;
  }

  l->var = malloc(sizeof(Var));
  l->next = malloc(sizeof(VarList));
  l->next->var = NULL;
  l->next->next = NULL;

  Var *var = l->var;

  var->name = malloc(strlen(name) + 1);
  strcpy(var->name, name);

  var->type = type;

  switch (type) {
  case INT:
    var->value = malloc(sizeof(int));
    if (value != NULL)
      memcpy(var->value, value, sizeof(int));
    break;
  case FLOAT:
    var->value = malloc(sizeof(float));
    if (value != NULL)
      memcpy(var->value, value, sizeof(float));
    break;
  case DOUBLE:
    var->value = malloc(sizeof(double));
    if (value != NULL)
      memcpy(var->value, value, sizeof(double));
    break;
  case VAR_CHAR:
    var->value = malloc(sizeof(char));
    if (value != NULL)
      memcpy(var->value, value, sizeof(char));
    break;
  case INT_ARRAY:  // ADICIONE ESTE CASO
    var->value = value;  // Já é um ponteiro para IntArray
    break;
  default:
    break;
  }

  return true;
}

bool update_var(VarType type, Var *var, void *value) {
  if (type <= VAR_CHAR) {
    double *num = value;
    switch (var->type) {
    case INT:
      int i = *num;
      memcpy(var->value, &i, sizeof(int));
      break;
    case FLOAT:
      float f = *num;
      memcpy(var->value, &f, sizeof(float));
      break;
    case DOUBLE:
      memcpy(var->value, num, sizeof(double));
      break;
    case VAR_CHAR:
      char c = *num;
      memcpy(var->value, &c, sizeof(char));
      break;
    default:
      return false;
      break;
    }

    return true;
  }

  return false;
}


bool add_int_array(char *name, int length) {
  if (length <= 0) {
    return false;
  }

  IntArray *arr = malloc(sizeof(IntArray));
  if (arr == NULL) {
    return false;
  }

  arr->length = length;
  arr->data = malloc(sizeof(int) * (size_t)length);
  if (arr->data == NULL) {
    free(arr);
    return false;
  }

  for (int i = 0; i < length; i++) {
    arr->data[i] = 0;
  }

  if (!add_var(INT_ARRAY, name, arr)) {
    free(arr->data);
    free(arr);
    return false;
  }

  return true;
}

IntArray *get_int_array(Var *var) {
  if (var == NULL || var->type != INT_ARRAY || var->value == NULL) {
    return NULL;
  }
  return (IntArray *)var->value;
}

bool get_int_array_elem(Var *var, int index, double *out_value) {
  IntArray *arr = get_int_array(var);
  if (arr == NULL || out_value == NULL) {
    return false;
  }
  if (index < 0 || index >= arr->length) {
    return false;
  }

  *out_value = (double)arr->data[index];
  return true;
}

bool set_int_array_elem(Var *var, int index, double value) {
  IntArray *arr = get_int_array(var);
  if (arr == NULL) {
    return false;
  }
  if (index < 0 || index >= arr->length) {
    return false;
  }

  arr->data[index] = (int)value;
  return true;
}

