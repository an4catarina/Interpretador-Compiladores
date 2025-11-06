#ifndef ERROR_H
#define ERROR_H

typedef enum {
  MULTIPLE_MAINS,
  SYNTAX_ERROR,
  DECL_INVALID_TYPE,
  INIT_INVALID_TYPE,
  UNKNOWN_SYMBOL,
  UNKNOWN_VAR,
  VAR_REDECLARATION,
  DIV_BY_ZERO,
  MOD_BY_ZERO,
} ErrorType;

extern void exit_with_error(const ErrorType e, int line);

#endif
