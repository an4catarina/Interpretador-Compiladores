#ifndef UTILS_H
#define UTILS_H

#include "ast.h"

extern double convert_char(char *c);
extern void print_var(ASTNode *node);
extern double get_var_value(char *name, int line);
extern char *strip_quotes(const char *parser_str);

#endif
