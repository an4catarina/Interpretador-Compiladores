#ifndef VAR_H
#define VAR_H

#include <stdbool.h>

typedef enum {
  INT,
  FLOAT,
  DOUBLE,
  VAR_CHAR,
  VAR,
  VAR_STRING,  /* NOVO: usado apenas em parâmetros (printf) */
} VarType;

extern const char *var_type_strings[];

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

#endif
