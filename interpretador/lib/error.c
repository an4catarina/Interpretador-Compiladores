#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void exit_with_error(const ErrorType e) {
  switch (e) {
  case DECL_INVALID_TYPE:
    fprintf(stderr, "[ERRO] Declaração de variável de tipo inválido\n");
    break;
  case INIT_INVALID_TYPE:
    fprintf(stderr, "[ERRO] Inicialização de variável de tipo inválido\n");
    break;
  case UNKNOWN_SYMBOL:
    fprintf(stderr, "[ERRO] Símbolo ou operação desconhecidos\n");
    break;
  default:
    break;
  }
  exit(1);
}