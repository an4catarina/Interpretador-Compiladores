#ifndef ERROR_H
#define ERROR_H

typedef enum {
  DECL_INVALID_TYPE,
  INIT_INVALID_TYPE,
  UNKNOWN_SYMBOL,
} ErrorType;

extern void exit_with_error(const ErrorType e);

#endif