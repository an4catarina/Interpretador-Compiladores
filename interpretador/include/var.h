#ifndef VAR_H
#define VAR_H

#include <stdbool.h>

typedef enum {
  INT,
  FLOAT,
  DOUBLE,
  VAR_CHAR,
  VAR,
  VAR_STRING,
  INT_ARRAY,
} VarType;

extern const char *var_type_strings[];

typedef struct {
  int length;
  int *data;
} IntArray;


typedef struct {
  VarType type;
  char *name;
  void *value;
} Var;

typedef struct VarList {
  Var *var;
  struct VarList *next;
} VarList;

extern VarList *create_var_list();
extern void free_var_list(VarList *v);
extern bool add_var(VarType type, char *name, void *value);
extern bool update_var(VarType type, Var *var, void *value);
extern Var *get_var(char *name);

bool add_int_array(char *name, int length);
IntArray *get_int_array(Var *var);
bool get_int_array_elem(Var *var, int index, double *out_value);
bool set_int_array_elem(Var *var, int index, double value);

#endif
